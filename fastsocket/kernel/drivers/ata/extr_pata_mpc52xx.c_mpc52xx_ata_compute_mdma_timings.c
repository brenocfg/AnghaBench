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
struct mpc52xx_ata_timings {int mdma1; int mdma2; scalar_t__ using_udma; } ;
struct mpc52xx_ata_priv {struct mdmaspec* mdmaspec; struct mpc52xx_ata_timings* timings; } ;
struct mdmaspec {int t0M; int td; int tkw; int tm; int th; int tj; int tn; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mpc52xx_ata_compute_mdma_timings(struct mpc52xx_ata_priv *priv, int dev,
				 int speed)
{
	struct mpc52xx_ata_timings *t = &priv->timings[dev];
	const struct mdmaspec *s = &priv->mdmaspec[speed];

	if (speed < 0 || speed > 2)
		return -EINVAL;

	t->mdma1 = (s->t0M << 24) | (s->td << 16) | (s->tkw << 8) | (s->tm);
	t->mdma2 = (s->th << 24) | (s->tj << 16) | (s->tn << 8);
	t->using_udma = 0;

	return 0;
}