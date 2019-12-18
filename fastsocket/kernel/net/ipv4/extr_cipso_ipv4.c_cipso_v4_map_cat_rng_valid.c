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
typedef  int u32 ;
typedef  int u16 ;
struct cipso_v4_doi {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CIPSO_V4_MAP_PASS ; 
 int CIPSO_V4_MAX_REM_CATS ; 
 int EFAULT ; 
 int get_unaligned_be16 (unsigned char const*) ; 

__attribute__((used)) static int cipso_v4_map_cat_rng_valid(const struct cipso_v4_doi *doi_def,
				      const unsigned char *rngcat,
				      u32 rngcat_len)
{
	u16 cat_high;
	u16 cat_low;
	u32 cat_prev = CIPSO_V4_MAX_REM_CATS + 1;
	u32 iter;

	if (doi_def->type != CIPSO_V4_MAP_PASS || rngcat_len & 0x01)
		return -EFAULT;

	for (iter = 0; iter < rngcat_len; iter += 4) {
		cat_high = get_unaligned_be16(&rngcat[iter]);
		if ((iter + 4) <= rngcat_len)
			cat_low = get_unaligned_be16(&rngcat[iter + 2]);
		else
			cat_low = 0;

		if (cat_high > cat_prev)
			return -EFAULT;

		cat_prev = cat_low;
	}

	return 0;
}