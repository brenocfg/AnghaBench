#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _lck_dev {int dummy; } ;
typedef  size_t s32 ;
struct TYPE_3__ {int /*<<< orphan*/  lckd_dev; scalar_t__ lckd_dev_bits; scalar_t__ lockeddev; scalar_t__ lck_cnt; scalar_t__ imm_len; scalar_t__ flags; scalar_t__ exi_idtime; scalar_t__ exi_id; int /*<<< orphan*/ * imm_buff; int /*<<< orphan*/ * CallbackTC; int /*<<< orphan*/ * CallbackEXT; int /*<<< orphan*/ * CallbackEXI; } ;
typedef  TYPE_1__ exibus_priv ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_LOCK_DEVS ; 
 size_t EXI_MAX_CHANNELS ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _lckdev_queue ; 
 int /*<<< orphan*/  lckdevs ; 

__attribute__((used)) static void __exi_initmap(exibus_priv *exim)
{
	s32 i;
	exibus_priv *m;

	__lwp_queue_initialize(&_lckdev_queue,lckdevs,EXI_LOCK_DEVS,sizeof(struct _lck_dev));

	for(i=0;i<EXI_MAX_CHANNELS;i++) {
		m = &exim[i];
		m->CallbackEXI = NULL;
		m->CallbackEXT = NULL;
		m->CallbackTC = NULL;
		m->imm_buff = NULL;
		m->exi_id = 0;
		m->exi_idtime = 0;
		m->flags = 0;
		m->imm_len = 0;
		m->lck_cnt = 0;
		m->lockeddev = 0;
		m->lckd_dev_bits = 0;
		__lwp_queue_init_empty(&m->lckd_dev);
	}
}