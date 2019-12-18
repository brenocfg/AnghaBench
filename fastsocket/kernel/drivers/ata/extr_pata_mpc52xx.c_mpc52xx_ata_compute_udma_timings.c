#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct udmaspec {int t2cyc; int tcyc; int tds; int tdh; int tdvs; int tdvh; int tfs; int tli; int tmli; int taz; int tenv; int tsr; int tss; int trfs; int trp; int tack; int tzah; } ;
struct mpc52xx_ata_timings {int udma1; int udma2; int udma3; int udma4; int udma5; int using_udma; } ;
struct mpc52xx_ata_priv {struct udmaspec* udmaspec; struct mpc52xx_ata_timings* timings; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mpc52xx_ata_compute_udma_timings(struct mpc52xx_ata_priv *priv, int dev,
				 int speed)
{
	struct mpc52xx_ata_timings *t = &priv->timings[dev];
	const struct udmaspec *s = &priv->udmaspec[speed];

	if (speed < 0 || speed > 2)
		return -EINVAL;

	t->udma1 = (s->t2cyc << 24) | (s->tcyc << 16) | (s->tds << 8) | s->tdh;
	t->udma2 = (s->tdvs << 24) | (s->tdvh << 16) | (s->tfs << 8) | s->tli;
	t->udma3 = (s->tmli << 24) | (s->taz << 16) | (s->tenv << 8) | s->tsr;
	t->udma4 = (s->tss << 24) | (s->trfs << 16) | (s->trp << 8) | s->tack;
	t->udma5 = (s->tzah << 24);
	t->using_udma = 1;

	return 0;
}