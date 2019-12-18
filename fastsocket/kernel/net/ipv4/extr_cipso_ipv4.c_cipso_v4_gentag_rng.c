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
struct TYPE_3__ {int /*<<< orphan*/  lvl; } ;
struct TYPE_4__ {TYPE_1__ mls; } ;
struct netlbl_lsm_secattr {int flags; TYPE_2__ attr; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 unsigned char CIPSO_V4_TAG_RANGE ; 
 int EPERM ; 
 int NETLBL_SECATTR_MLS_CAT ; 
 int NETLBL_SECATTR_MLS_LVL ; 
 int cipso_v4_map_cat_rng_hton (struct cipso_v4_doi const*,struct netlbl_lsm_secattr const*,unsigned char*,int) ; 
 int cipso_v4_map_lvl_hton (struct cipso_v4_doi const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int cipso_v4_gentag_rng(const struct cipso_v4_doi *doi_def,
			       const struct netlbl_lsm_secattr *secattr,
			       unsigned char *buffer,
			       u32 buffer_len)
{
	int ret_val;
	u32 tag_len;
	u32 level;

	if (!(secattr->flags & NETLBL_SECATTR_MLS_LVL))
		return -EPERM;

	ret_val = cipso_v4_map_lvl_hton(doi_def,
					secattr->attr.mls.lvl,
					&level);
	if (ret_val != 0)
		return ret_val;

	if (secattr->flags & NETLBL_SECATTR_MLS_CAT) {
		ret_val = cipso_v4_map_cat_rng_hton(doi_def,
						    secattr,
						    &buffer[4],
						    buffer_len - 4);
		if (ret_val < 0)
			return ret_val;

		tag_len = 4 + ret_val;
	} else
		tag_len = 4;

	buffer[0] = CIPSO_V4_TAG_RANGE;
	buffer[1] = tag_len;
	buffer[3] = level;

	return tag_len;
}