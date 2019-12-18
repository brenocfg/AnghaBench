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
typedef  int u32 ;
struct TYPE_4__ {TYPE_2__* std; } ;
struct cipso_v4_doi {int type; TYPE_1__ map; } ;
struct TYPE_6__ {int cipso_size; int* cipso; } ;
struct TYPE_5__ {TYPE_3__ cat; } ;

/* Variables and functions */
 int CIPSO_V4_INV_CAT ; 
#define  CIPSO_V4_MAP_PASS 129 
#define  CIPSO_V4_MAP_TRANS 128 
 int EFAULT ; 
 int cipso_v4_bitmap_walk (unsigned char const*,int,int,int) ; 

__attribute__((used)) static int cipso_v4_map_cat_rbm_valid(const struct cipso_v4_doi *doi_def,
				      const unsigned char *bitmap,
				      u32 bitmap_len)
{
	int cat = -1;
	u32 bitmap_len_bits = bitmap_len * 8;
	u32 cipso_cat_size;
	u32 *cipso_array;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		return 0;
	case CIPSO_V4_MAP_TRANS:
		cipso_cat_size = doi_def->map.std->cat.cipso_size;
		cipso_array = doi_def->map.std->cat.cipso;
		for (;;) {
			cat = cipso_v4_bitmap_walk(bitmap,
						   bitmap_len_bits,
						   cat + 1,
						   1);
			if (cat < 0)
				break;
			if (cat >= cipso_cat_size ||
			    cipso_array[cat] >= CIPSO_V4_INV_CAT)
				return -EFAULT;
		}

		if (cat == -1)
			return 0;
		break;
	}

	return -EFAULT;
}