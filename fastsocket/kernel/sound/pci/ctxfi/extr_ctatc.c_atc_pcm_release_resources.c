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
struct sum_mgr {int /*<<< orphan*/  (* put_src ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_sum ) (struct sum_mgr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* put_amixer ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_srcimp ) (struct sum_mgr*,struct srcimp*) ;} ;
struct srcimp_mgr {int /*<<< orphan*/  (* put_src ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_sum ) (struct sum_mgr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* put_amixer ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_srcimp ) (struct sum_mgr*,struct srcimp*) ;} ;
struct srcimp {TYPE_1__* ops; } ;
struct src_mgr {int /*<<< orphan*/  (* put_src ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_sum ) (struct sum_mgr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* put_amixer ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_srcimp ) (struct sum_mgr*,struct srcimp*) ;} ;
struct ct_atc_pcm {int n_srcimp; int n_srcc; int n_amixer; int /*<<< orphan*/ * vm_block; struct srcimp* src; int /*<<< orphan*/ * mono; struct srcimp** amixers; struct srcimp** srccs; struct srcimp** srcimps; } ;
struct ct_atc {struct sum_mgr** rsc_mgrs; } ;
struct amixer_mgr {int /*<<< orphan*/  (* put_src ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_sum ) (struct sum_mgr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* put_amixer ) (struct sum_mgr*,struct srcimp*) ;int /*<<< orphan*/  (* put_srcimp ) (struct sum_mgr*,struct srcimp*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap ) (struct srcimp*) ;} ;

/* Variables and functions */
 size_t AMIXER ; 
 size_t SRC ; 
 size_t SRCIMP ; 
 size_t SUM ; 
 int /*<<< orphan*/  ct_unmap_audio_buffer (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  kfree (struct srcimp**) ; 
 int /*<<< orphan*/  stub1 (struct srcimp*) ; 
 int /*<<< orphan*/  stub2 (struct sum_mgr*,struct srcimp*) ; 
 int /*<<< orphan*/  stub3 (struct sum_mgr*,struct srcimp*) ; 
 int /*<<< orphan*/  stub4 (struct sum_mgr*,struct srcimp*) ; 
 int /*<<< orphan*/  stub5 (struct sum_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct sum_mgr*,struct srcimp*) ; 

__attribute__((used)) static int
atc_pcm_release_resources(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src_mgr *src_mgr = atc->rsc_mgrs[SRC];
	struct srcimp_mgr *srcimp_mgr = atc->rsc_mgrs[SRCIMP];
	struct amixer_mgr *amixer_mgr = atc->rsc_mgrs[AMIXER];
	struct sum_mgr *sum_mgr = atc->rsc_mgrs[SUM];
	struct srcimp *srcimp;
	int i;

	if (apcm->srcimps) {
		for (i = 0; i < apcm->n_srcimp; i++) {
			srcimp = apcm->srcimps[i];
			srcimp->ops->unmap(srcimp);
			srcimp_mgr->put_srcimp(srcimp_mgr, srcimp);
			apcm->srcimps[i] = NULL;
		}
		kfree(apcm->srcimps);
		apcm->srcimps = NULL;
	}

	if (apcm->srccs) {
		for (i = 0; i < apcm->n_srcc; i++) {
			src_mgr->put_src(src_mgr, apcm->srccs[i]);
			apcm->srccs[i] = NULL;
		}
		kfree(apcm->srccs);
		apcm->srccs = NULL;
	}

	if (apcm->amixers) {
		for (i = 0; i < apcm->n_amixer; i++) {
			amixer_mgr->put_amixer(amixer_mgr, apcm->amixers[i]);
			apcm->amixers[i] = NULL;
		}
		kfree(apcm->amixers);
		apcm->amixers = NULL;
	}

	if (apcm->mono) {
		sum_mgr->put_sum(sum_mgr, apcm->mono);
		apcm->mono = NULL;
	}

	if (apcm->src) {
		src_mgr->put_src(src_mgr, apcm->src);
		apcm->src = NULL;
	}

	if (apcm->vm_block) {
		/* Undo device virtual mem map */
		ct_unmap_audio_buffer(atc, apcm);
		apcm->vm_block = NULL;
	}

	return 0;
}