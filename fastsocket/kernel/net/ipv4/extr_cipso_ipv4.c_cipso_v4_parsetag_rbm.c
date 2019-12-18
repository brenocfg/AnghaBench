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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * cat; int /*<<< orphan*/  lvl; } ;
struct TYPE_4__ {TYPE_1__ mls; } ;
struct netlbl_lsm_secattr {int /*<<< orphan*/  flags; TYPE_2__ attr; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETLBL_SECATTR_MLS_CAT ; 
 int /*<<< orphan*/  NETLBL_SECATTR_MLS_LVL ; 
 int cipso_v4_map_cat_rbm_ntoh (struct cipso_v4_doi const*,unsigned char const*,int,struct netlbl_lsm_secattr*) ; 
 int cipso_v4_map_lvl_ntoh (struct cipso_v4_doi const*,unsigned char const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * netlbl_secattr_catmap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlbl_secattr_catmap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipso_v4_parsetag_rbm(const struct cipso_v4_doi *doi_def,
				 const unsigned char *tag,
				 struct netlbl_lsm_secattr *secattr)
{
	int ret_val;
	u8 tag_len = tag[1];
	u32 level;

	ret_val = cipso_v4_map_lvl_ntoh(doi_def, tag[3], &level);
	if (ret_val != 0)
		return ret_val;
	secattr->attr.mls.lvl = level;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;

	if (tag_len > 4) {
		secattr->attr.mls.cat =
		                       netlbl_secattr_catmap_alloc(GFP_ATOMIC);
		if (secattr->attr.mls.cat == NULL)
			return -ENOMEM;

		ret_val = cipso_v4_map_cat_rbm_ntoh(doi_def,
						    &tag[4],
						    tag_len - 4,
						    secattr);
		if (ret_val != 0) {
			netlbl_secattr_catmap_free(secattr->attr.mls.cat);
			return ret_val;
		}

		secattr->flags |= NETLBL_SECATTR_MLS_CAT;
	}

	return 0;
}