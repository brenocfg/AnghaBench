#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tvnorm; int /*<<< orphan*/  setup_ok; } ;
struct bttv_fh {int /*<<< orphan*/  ovfmt; TYPE_4__ ov; int /*<<< orphan*/  do_crop; struct bttv* btv; } ;
struct bttv_buffer {int /*<<< orphan*/  crop; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct bttv {TYPE_3__* crop; int /*<<< orphan*/  tvnorm; TYPE_2__ c; TYPE_1__ fbuf; } ;
struct TYPE_7__ {int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  bttv_overlay_risc (struct bttv*,TYPE_4__*,int /*<<< orphan*/ ,struct bttv_buffer*) ; 
 int bttv_switch_overlay (struct bttv*,struct bttv_fh*,struct bttv_buffer*) ; 
 int /*<<< orphan*/  check_alloc_btres_lock (struct bttv*,struct bttv_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct bttv_buffer* videobuf_sg_alloc (int) ; 

__attribute__((used)) static int bttv_overlay(struct file *file, void *f, unsigned int on)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;
	struct bttv_buffer *new;
	int retval = 0;

	if (on) {
		/* verify args */
		if (unlikely(!btv->fbuf.base)) {
			return -EINVAL;
		}
		if (unlikely(!fh->ov.setup_ok)) {
			dprintk("bttv%d: overlay: !setup_ok\n", btv->c.nr);
			retval = -EINVAL;
		}
		if (retval)
			return retval;
	}

	if (!check_alloc_btres_lock(btv, fh, RESOURCE_OVERLAY))
		return -EBUSY;

	if (on) {
		fh->ov.tvnorm = btv->tvnorm;
		new = videobuf_sg_alloc(sizeof(*new));
		new->crop = btv->crop[!!fh->do_crop].rect;
		bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
	} else {
		new = NULL;
	}

	/* switch over */
	retval = bttv_switch_overlay(btv, fh, new);
	return retval;
}