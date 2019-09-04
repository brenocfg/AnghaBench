#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct bpf_d {scalar_t__ bd_state; int bd_flags; TYPE_1__ bd_sel; scalar_t__ bd_sig; scalar_t__ bd_sigio; scalar_t__ bd_async; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ BPF_IDLE ; 
 int BPF_KNOTE ; 
 scalar_t__ BPF_WAITING ; 
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bpf_stop_timer (struct bpf_d*) ; 
 int /*<<< orphan*/  pgsigio (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bpf_wakeup(struct bpf_d *d)
{
	if (d->bd_state == BPF_WAITING) {
		bpf_stop_timer(d);
		d->bd_state = BPF_IDLE;
	}
	wakeup((caddr_t)d);
	if (d->bd_async && d->bd_sig && d->bd_sigio)
		pgsigio(d->bd_sigio, d->bd_sig);

	selwakeup(&d->bd_sel);
	if ((d->bd_flags & BPF_KNOTE))
		KNOTE(&d->bd_sel.si_note, 1);
}