#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  cat; } ;
struct TYPE_4__ {TYPE_1__ mls; } ;
struct netlbl_lsm_secattr {TYPE_2__ attr; } ;
struct cipso_v4_doi {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  htons (int) ; 
 int netlbl_secattr_catmap_walk (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cipso_v4_map_cat_enum_hton(const struct cipso_v4_doi *doi_def,
				      const struct netlbl_lsm_secattr *secattr,
				      unsigned char *net_cat,
				      u32 net_cat_len)
{
	int cat = -1;
	u32 cat_iter = 0;

	for (;;) {
		cat = netlbl_secattr_catmap_walk(secattr->attr.mls.cat,
						 cat + 1);
		if (cat < 0)
			break;
		if ((cat_iter + 2) > net_cat_len)
			return -ENOSPC;

		*((__be16 *)&net_cat[cat_iter]) = htons(cat);
		cat_iter += 2;
	}

	return cat_iter;
}