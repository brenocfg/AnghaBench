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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  get_unaligned_be16 (unsigned char const*) ; 
 int netlbl_secattr_catmap_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cipso_v4_map_cat_enum_ntoh(const struct cipso_v4_doi *doi_def,
				      const unsigned char *net_cat,
				      u32 net_cat_len,
				      struct netlbl_lsm_secattr *secattr)
{
	int ret_val;
	u32 iter;

	for (iter = 0; iter < net_cat_len; iter += 2) {
		ret_val = netlbl_secattr_catmap_setbit(secattr->attr.mls.cat,
				get_unaligned_be16(&net_cat[iter]),
				GFP_ATOMIC);
		if (ret_val != 0)
			return ret_val;
	}

	return 0;
}