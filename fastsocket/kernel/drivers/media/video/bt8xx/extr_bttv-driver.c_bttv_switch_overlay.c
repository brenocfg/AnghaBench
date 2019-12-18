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
struct bttv_fh {int /*<<< orphan*/  cap; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct bttv_buffer {TYPE_1__ vb; } ;
struct bttv {int loop_irq; int /*<<< orphan*/  s_lock; struct bttv_buffer* screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  bttv_dma_free (int /*<<< orphan*/ *,struct bttv*,struct bttv_buffer*) ; 
 int /*<<< orphan*/  bttv_set_dma (struct bttv*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  free_btres_lock (struct bttv*,struct bttv_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bttv_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bttv_switch_overlay(struct bttv *btv, struct bttv_fh *fh,
		    struct bttv_buffer *new)
{
	struct bttv_buffer *old;
	unsigned long flags;
	int retval = 0;

	dprintk("switch_overlay: enter [new=%p]\n",new);
	if (new)
		new->vb.state = VIDEOBUF_DONE;
	spin_lock_irqsave(&btv->s_lock,flags);
	old = btv->screen;
	btv->screen = new;
	btv->loop_irq |= 1;
	bttv_set_dma(btv, 0x03);
	spin_unlock_irqrestore(&btv->s_lock,flags);
	if (NULL != old) {
		dprintk("switch_overlay: old=%p state is %d\n",old,old->vb.state);
		bttv_dma_free(&fh->cap,btv, old);
		kfree(old);
	}
	if (NULL == new)
		free_btres_lock(btv,fh,RESOURCE_OVERLAY);
	dprintk("switch_overlay: done\n");
	return retval;
}