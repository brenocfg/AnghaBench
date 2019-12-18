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
struct rxpd {int /*<<< orphan*/  nf; int /*<<< orphan*/  snr; } ;
struct lbs_private {size_t numSNRNF; size_t nextSNRNF; int /*<<< orphan*/ * rawNF; int /*<<< orphan*/ * rawSNR; } ;

/* Variables and functions */
 size_t DEFAULT_DATA_AVG_FACTOR ; 

__attribute__((used)) static void lbs_save_rawSNRNF(struct lbs_private *priv, struct rxpd *p_rx_pd)
{
	if (priv->numSNRNF < DEFAULT_DATA_AVG_FACTOR)
		priv->numSNRNF++;
	priv->rawSNR[priv->nextSNRNF] = p_rx_pd->snr;
	priv->rawNF[priv->nextSNRNF] = p_rx_pd->nf;
	priv->nextSNRNF++;
	if (priv->nextSNRNF >= DEFAULT_DATA_AVG_FACTOR)
		priv->nextSNRNF = 0;
	return;
}