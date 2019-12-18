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
typedef  size_t u8 ;
typedef  int u16 ;
struct lbs_private {size_t numSNRNF; scalar_t__* rawNF; } ;

/* Variables and functions */

__attribute__((used)) static u8 lbs_getavgnf(struct lbs_private *priv)
{
	u8 i;
	u16 temp = 0;
	if (priv->numSNRNF == 0)
		return 0;
	for (i = 0; i < priv->numSNRNF; i++)
		temp += priv->rawNF[i];
	return (u8) (temp / priv->numSNRNF);

}