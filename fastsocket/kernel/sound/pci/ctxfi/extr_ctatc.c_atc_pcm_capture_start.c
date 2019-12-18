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
struct src_mgr {int /*<<< orphan*/  (* commit_write ) (struct src_mgr*) ;int /*<<< orphan*/  (* src_enable_s ) (struct src_mgr*,struct src*) ;int /*<<< orphan*/  (* src_disable ) (struct src_mgr*,struct src*) ;} ;
struct src {TYPE_4__* ops; } ;
struct ct_atc_pcm {int started; int n_srcc; int /*<<< orphan*/  timer; struct src* src; struct src** srccs; TYPE_3__* vm_block; TYPE_2__* substream; } ;
struct ct_atc {struct src_mgr** rsc_mgrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* commit_write ) (struct src*) ;int /*<<< orphan*/  (* set_state ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_bm ) (struct src*,int) ;int /*<<< orphan*/  (* set_ca ) (struct src*,scalar_t__) ;int /*<<< orphan*/  (* set_la ) (struct src*,scalar_t__) ;int /*<<< orphan*/  (* set_sa ) (struct src*,scalar_t__) ;int /*<<< orphan*/  (* set_sf ) (struct src*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_pm ) (struct src*,int) ;} ;
struct TYPE_7__ {scalar_t__ addr; scalar_t__ size; } ;
struct TYPE_6__ {TYPE_1__* runtime; } ;
struct TYPE_5__ {int channels; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 size_t SRC ; 
 int /*<<< orphan*/  SRC_STATE_RUN ; 
 int /*<<< orphan*/  convert_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_timer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct src*,int) ; 
 int /*<<< orphan*/  stub10 (struct src*) ; 
 int /*<<< orphan*/  stub11 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub12 (struct src*,int) ; 
 int /*<<< orphan*/  stub13 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct src*) ; 
 int /*<<< orphan*/  stub15 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub16 (struct src_mgr*) ; 
 int /*<<< orphan*/  stub2 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub3 (struct src*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (struct src*,scalar_t__) ; 
 int /*<<< orphan*/  stub7 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub8 (struct src_mgr*) ; 
 int /*<<< orphan*/  stub9 (struct src*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atc_pcm_capture_start(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src *src;
	struct src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	int i, multi;

	if (apcm->started)
		return 0;

	apcm->started = 1;
	multi = apcm->substream->runtime->channels;
	/* Set up converting SRCs */
	for (i = 0; i < apcm->n_srcc; i++) {
		src = apcm->srccs[i];
		src->ops->set_pm(src, ((i%multi) != (multi-1)));
		src_mgr->src_disable(src_mgr, src);
	}

	/*  Set up recording SRC */
	src = apcm->src;
	src->ops->set_sf(src, convert_format(apcm->substream->runtime->format));
	src->ops->set_sa(src, apcm->vm_block->addr);
	src->ops->set_la(src, apcm->vm_block->addr + apcm->vm_block->size);
	src->ops->set_ca(src, apcm->vm_block->addr);
	src_mgr->src_disable(src_mgr, src);

	/* Disable relevant SRCs firstly */
	src_mgr->commit_write(src_mgr);

	/* Enable SRCs respectively */
	for (i = 0; i < apcm->n_srcc; i++) {
		src = apcm->srccs[i];
		src->ops->set_state(src, SRC_STATE_RUN);
		src->ops->commit_write(src);
		src_mgr->src_enable_s(src_mgr, src);
	}
	src = apcm->src;
	src->ops->set_bm(src, 1);
	src->ops->set_state(src, SRC_STATE_RUN);
	src->ops->commit_write(src);
	src_mgr->src_enable_s(src_mgr, src);

	/* Enable relevant SRCs synchronously */
	src_mgr->commit_write(src_mgr);

	ct_timer_start(apcm->timer);
	return 0;
}