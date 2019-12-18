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
struct sum {int /*<<< orphan*/  rsc; } ;
struct ct_mixer {struct sum** sums; struct amixer** amixers; } ;
struct amixer {TYPE_1__* ops; int /*<<< orphan*/  rsc; } ;
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;
struct TYPE_2__ {int /*<<< orphan*/  (* setup ) (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ;} ;

/* Variables and functions */
 int AMIXER_LINEIN ; 
 int AMIXER_LINEIN_C ; 
 int AMIXER_MASTER_F ; 
 int AMIXER_MASTER_F_C ; 
 int AMIXER_MASTER_S ; 
 int AMIXER_MIC ; 
 int AMIXER_MIC_C ; 
 int AMIXER_PCM_F ; 
 int AMIXER_PCM_F_C ; 
 int AMIXER_PCM_S ; 
 int AMIXER_SPDIFI ; 
 int AMIXER_SPDIFI_C ; 
 int AMIXER_SPDIFO ; 
 int AMIXER_WAVE_F ; 
 int AMIXER_WAVE_S ; 
 int CHN_NUM ; 
 int /*<<< orphan*/  INIT_VOL ; 
 int SUM_IN_F ; 
 int SUM_IN_F_C ; 
 int /*<<< orphan*/  stub1 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub10 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub11 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub12 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub13 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub14 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub15 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub16 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub17 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub18 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub19 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub2 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub20 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub21 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub22 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub23 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub24 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub3 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub4 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub5 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub6 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub7 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub8 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 
 int /*<<< orphan*/  stub9 (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sum*) ; 

__attribute__((used)) static int ct_mixer_topology_build(struct ct_mixer *mixer)
{
	struct sum *sum;
	struct amixer *amix_d, *amix_s;
	enum CT_AMIXER_CTL i, j;

	/* Build topology from destination to source */

	/* Set up Master mixer */
	for (i = AMIXER_MASTER_F, j = SUM_IN_F;
					i <= AMIXER_MASTER_S; i++, j++) {
		amix_d = mixer->amixers[i*CHN_NUM];
		sum = mixer->sums[j*CHN_NUM];
		amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, NULL);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		sum = mixer->sums[j*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, NULL);
	}

	/* Set up Wave-out mixer */
	for (i = AMIXER_WAVE_F, j = AMIXER_MASTER_F;
					i <= AMIXER_WAVE_S; i++, j++) {
		amix_d = mixer->amixers[i*CHN_NUM];
		amix_s = mixer->amixers[j*CHN_NUM];
		amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, NULL);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		amix_s = mixer->amixers[j*CHN_NUM+1];
		amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, NULL);
	}

	/* Set up S/PDIF-out mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFO*CHN_NUM];
	amix_s = mixer->amixers[AMIXER_MASTER_F*CHN_NUM];
	amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, NULL);
	amix_d = mixer->amixers[AMIXER_SPDIFO*CHN_NUM+1];
	amix_s = mixer->amixers[AMIXER_MASTER_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &amix_s->rsc, INIT_VOL, NULL);

	/* Set up PCM-in mixer */
	for (i = AMIXER_PCM_F, j = SUM_IN_F; i <= AMIXER_PCM_S; i++, j++) {
		amix_d = mixer->amixers[i*CHN_NUM];
		sum = mixer->sums[j*CHN_NUM];
		amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
		amix_d = mixer->amixers[i*CHN_NUM+1];
		sum = mixer->sums[j*CHN_NUM+1];
		amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	}

	/* Set up Line-in mixer */
	amix_d = mixer->amixers[AMIXER_LINEIN*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_LINEIN*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up Mic-in mixer */
	amix_d = mixer->amixers[AMIXER_MIC*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_MIC*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up S/PDIF-in mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFI*CHN_NUM];
	sum = mixer->sums[SUM_IN_F*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_SPDIFI*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up Master recording mixer */
	amix_d = mixer->amixers[AMIXER_MASTER_F_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, NULL);
	amix_d = mixer->amixers[AMIXER_MASTER_F_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, &sum->rsc, INIT_VOL, NULL);

	/* Set up PCM-in recording mixer */
	amix_d = mixer->amixers[AMIXER_PCM_F_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_PCM_F_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up Line-in recording mixer */
	amix_d = mixer->amixers[AMIXER_LINEIN_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_LINEIN_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up Mic-in recording mixer */
	amix_d = mixer->amixers[AMIXER_MIC_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_MIC_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	/* Set up S/PDIF-in recording mixer */
	amix_d = mixer->amixers[AMIXER_SPDIFI_C*CHN_NUM];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);
	amix_d = mixer->amixers[AMIXER_SPDIFI_C*CHN_NUM+1];
	sum = mixer->sums[SUM_IN_F_C*CHN_NUM+1];
	amix_d->ops->setup(amix_d, NULL, INIT_VOL, sum);

	return 0;
}