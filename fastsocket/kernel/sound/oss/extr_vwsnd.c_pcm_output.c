#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int hwbuf_max; int hwbuf_size; int swbuf_size; int hw_fragsize; int flags; scalar_t__ hwstate; scalar_t__ swstate; int const swb_i_avail; int swb_i_idx; int byte_count; int frame_size; int frag_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; scalar_t__ MSC_offset; int /*<<< orphan*/  chan; } ;
typedef  TYPE_1__ vwsnd_port_t ;
typedef  scalar_t__ vwsnd_port_swstate_t ;
typedef  scalar_t__ vwsnd_port_hwstate_t ;
struct TYPE_11__ {TYPE_1__ wport; } ;
typedef  TYPE_2__ vwsnd_dev_t ;
struct TYPE_12__ {scalar_t__ msc; } ;
typedef  TYPE_3__ ustmsc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBGEV (char*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  DBGP (char*,int const,...) ; 
 int /*<<< orphan*/  DBGPV (char*,...) ; 
 int /*<<< orphan*/  DBGRV () ; 
 int DISABLED ; 
 int ERFLOWN ; 
 int HW_BUSY ; 
 scalar_t__ HW_RUNNING ; 
 scalar_t__ HW_STOPPED ; 
 scalar_t__ SW_DRAIN ; 
 scalar_t__ SW_INITIAL ; 
 scalar_t__ SW_OFF ; 
 scalar_t__ SW_RUN ; 
 int /*<<< orphan*/  __swb_inc_i (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __swb_inc_u (TYPE_1__*,int) ; 
 int /*<<< orphan*/  li_activate_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  li_deactivate_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  li_read_USTMSC (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int li_read_hwptr (int /*<<< orphan*/ *) ; 
 int li_read_swptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  li_write_swptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcm_copy_out (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcm_output(vwsnd_dev_t *devc, int erflown, int nb)
{
	vwsnd_port_t *wport = &devc->wport;
	const int hwmax  = wport->hwbuf_max;
	const int hwsize = wport->hwbuf_size;
	const int swsize = wport->swbuf_size;
	const int fragsize = wport->hw_fragsize;
	unsigned long iflags;

	DBGEV("(devc=0x%p, erflown=%d, nb=%d)\n", devc, erflown, nb);
	spin_lock_irqsave(&wport->lock, iflags);
	if (erflown)
		wport->flags |= ERFLOWN;
	(void) __swb_inc_u(wport, nb);
	if (wport->flags & HW_BUSY) {
		spin_unlock_irqrestore(&wport->lock, iflags);
		DBGPV("returning: HW BUSY\n");
		return;
	}
	if (wport->flags & DISABLED) {
		spin_unlock_irqrestore(&wport->lock, iflags);
		DBGPV("returning: DISABLED\n");
		return;
	}
	wport->flags |= HW_BUSY;
	while (1) {
		int swptr, hwptr, hw_avail, sw_avail, swidx;
		vwsnd_port_hwstate_t hwstate = wport->hwstate;
		vwsnd_port_swstate_t swstate = wport->swstate;
		int hw_unavail;
		ustmsc_t ustmsc;

		hwptr = li_read_hwptr(&wport->chan);
		swptr = li_read_swptr(&wport->chan);
		hw_unavail = (swptr - hwptr + hwsize) % hwsize;
		hw_avail = (hwmax - hw_unavail) & -fragsize;
		sw_avail = wport->swb_i_avail & -fragsize;
		if (sw_avail && swstate == SW_RUN) {
			if (wport->flags & ERFLOWN) {
				wport->flags &= ~ERFLOWN;
			}
		} else if (swstate == SW_INITIAL ||
			 swstate == SW_OFF ||
			 (swstate == SW_DRAIN &&
			  !sw_avail &&
			  (wport->flags & ERFLOWN))) {
			DBGP("stopping.  hwstate = %d\n", hwstate);
			if (hwstate != HW_STOPPED) {
				li_deactivate_dma(&wport->chan);
				wport->hwstate = HW_STOPPED;
			}
			wake_up(&wport->queue);
			break;
		}
		if (!sw_avail || !hw_avail)
			break;
		spin_unlock_irqrestore(&wport->lock, iflags);

		/*
		 * We gave up the port lock, but we have the HW_BUSY flag.
		 * Proceed without accessing any nonlocal state.
		 * Do not exit the loop -- must check for more work.
		 */

		swidx = wport->swb_i_idx;
		nb = hw_avail;
		if (nb > sw_avail)
			nb = sw_avail;
		if (nb > hwsize - swptr)
			nb = hwsize - swptr; /* don't overflow hwbuf */
		if (nb > swsize - swidx)
			nb = swsize - swidx; /* don't overflow swbuf */
		ASSERT(nb > 0);
		if (nb % fragsize) {
			DBGP("nb = %d, fragsize = %d\n", nb, fragsize);
			DBGP("hw_avail = %d\n", hw_avail);
			DBGP("sw_avail = %d\n", sw_avail);
			DBGP("hwsize = %d, swptr = %d\n", hwsize, swptr);
			DBGP("swsize = %d, swidx = %d\n", swsize, swidx);
		}
		ASSERT(!(nb % fragsize));
		DBGPV("copying swb[%d..%d] to hwb[%d..%d]\n",
		      swidx, swidx + nb, swptr, swptr + nb);
		pcm_copy_out(wport, swidx, swptr, nb);
		li_write_swptr(&wport->chan, (swptr + nb) % hwsize);
		spin_lock_irqsave(&wport->lock, iflags);
		if (hwstate == HW_STOPPED) {
			DBGPV("starting\n");
			li_activate_dma(&wport->chan);
			wport->hwstate = HW_RUNNING;
			li_read_USTMSC(&wport->chan, &ustmsc);
			ASSERT(wport->byte_count % wport->frame_size == 0);
			wport->MSC_offset = ustmsc.msc - wport->byte_count / wport->frame_size;
		}
		__swb_inc_i(wport, nb);
		wport->byte_count += nb;
		wport->frag_count += nb / fragsize;
		ASSERT(nb % fragsize == 0);
		wake_up(&wport->queue);
	}
	wport->flags &= ~HW_BUSY;
	spin_unlock_irqrestore(&wport->lock, iflags);
	DBGRV();
}