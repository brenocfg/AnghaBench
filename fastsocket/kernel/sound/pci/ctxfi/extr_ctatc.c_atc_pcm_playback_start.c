#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int msr; } ;
struct src {unsigned int multi; TYPE_3__* ops; TYPE_1__ rsc; } ;
struct ct_atc_pcm {int started; int /*<<< orphan*/  timer; TYPE_2__* vm_block; struct src* src; } ;
struct ct_atc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* commit_write ) (struct src*) ;int /*<<< orphan*/  (* set_state ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_bm ) (struct src*,int) ;int /*<<< orphan*/  (* set_cisz ) (struct src*,unsigned int) ;int /*<<< orphan*/  (* set_ca ) (struct src*,scalar_t__) ;int /*<<< orphan*/  (* set_la ) (struct src*,scalar_t__) ;int /*<<< orphan*/  (* set_sa ) (struct src*,scalar_t__) ;} ;
struct TYPE_5__ {scalar_t__ addr; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_STATE_INIT ; 
 int /*<<< orphan*/  ct_timer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct src*,unsigned int) ; 
 int /*<<< orphan*/  stub5 (struct src*,int) ; 
 int /*<<< orphan*/  stub6 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct src*) ; 

__attribute__((used)) static int atc_pcm_playback_start(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	unsigned int max_cisz;
	struct src *src = apcm->src;

	if (apcm->started)
		return 0;
	apcm->started = 1;

	max_cisz = src->multi * src->rsc.msr;
	max_cisz = 0x80 * (max_cisz < 8 ? max_cisz : 8);

	src->ops->set_sa(src, apcm->vm_block->addr);
	src->ops->set_la(src, apcm->vm_block->addr + apcm->vm_block->size);
	src->ops->set_ca(src, apcm->vm_block->addr + max_cisz);
	src->ops->set_cisz(src, max_cisz);

	src->ops->set_bm(src, 1);
	src->ops->set_state(src, SRC_STATE_INIT);
	src->ops->commit_write(src);

	ct_timer_start(apcm->timer);
	return 0;
}