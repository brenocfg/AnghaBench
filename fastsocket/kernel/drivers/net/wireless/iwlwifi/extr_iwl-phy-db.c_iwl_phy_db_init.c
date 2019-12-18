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
struct iwl_trans {int dummy; } ;
struct iwl_phy_db {struct iwl_trans* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iwl_phy_db* kzalloc (int,int /*<<< orphan*/ ) ; 

struct iwl_phy_db *iwl_phy_db_init(struct iwl_trans *trans)
{
	struct iwl_phy_db *phy_db = kzalloc(sizeof(struct iwl_phy_db),
					    GFP_KERNEL);

	if (!phy_db)
		return phy_db;

	phy_db->trans = trans;

	/* TODO: add default values of the phy db. */
	return phy_db;
}