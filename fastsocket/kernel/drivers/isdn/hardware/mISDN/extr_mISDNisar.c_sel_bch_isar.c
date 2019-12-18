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
typedef  int u8 ;
struct isar_hw {struct isar_ch* ch; } ;
struct isar_ch {int dpath; } ;

/* Variables and functions */

__attribute__((used)) static inline struct isar_ch *
sel_bch_isar(struct isar_hw *isar, u8 dpath)
{
	struct isar_ch	*base = &isar->ch[0];

	if ((!dpath) || (dpath > 2))
		return NULL;
	if (base->dpath == dpath)
		return base;
	base++;
	if (base->dpath == dpath)
		return base;
	return NULL;
}