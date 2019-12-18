#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pg_help_data {int num_of_pg; TYPE_1__* data; } ;
struct dcbx_ets_feature {int /*<<< orphan*/  pg_bw_tbl; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {scalar_t__ pg; scalar_t__ num_of_dif_pri; int /*<<< orphan*/  pg_priority; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int DCBX_PG_BW_GET (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DCBX_PG_BW_SET (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ DCBX_STRICT_PRI_PG ; 
 int EINVAL ; 

__attribute__((used)) static int bnx2x_dcbx_join_pgs(
			      struct bnx2x            *bp,
			      struct dcbx_ets_feature *ets,
			      struct pg_help_data     *pg_help_data,
			      u8                      required_num_of_pg)
{
	u8 entry_joined    = pg_help_data->num_of_pg - 1;
	u8 entry_removed   = entry_joined + 1;
	u8 pg_joined       = 0;

	if (required_num_of_pg == 0 || ARRAY_SIZE(pg_help_data->data)
						<= pg_help_data->num_of_pg) {

		BNX2X_ERR("required_num_of_pg can't be zero\n");
		return -EINVAL;
	}

	while (required_num_of_pg < pg_help_data->num_of_pg) {
		entry_joined = pg_help_data->num_of_pg - 2;
		entry_removed = entry_joined + 1;
		/* protect index */
		entry_removed %= ARRAY_SIZE(pg_help_data->data);

		pg_help_data->data[entry_joined].pg_priority |=
			pg_help_data->data[entry_removed].pg_priority;

		pg_help_data->data[entry_joined].num_of_dif_pri +=
			pg_help_data->data[entry_removed].num_of_dif_pri;

		if (pg_help_data->data[entry_joined].pg == DCBX_STRICT_PRI_PG ||
		    pg_help_data->data[entry_removed].pg == DCBX_STRICT_PRI_PG)
			/* Entries joined strict priority rules */
			pg_help_data->data[entry_joined].pg =
							DCBX_STRICT_PRI_PG;
		else {
			/* Entries can be joined join BW */
			pg_joined = DCBX_PG_BW_GET(ets->pg_bw_tbl,
					pg_help_data->data[entry_joined].pg) +
				    DCBX_PG_BW_GET(ets->pg_bw_tbl,
					pg_help_data->data[entry_removed].pg);

			DCBX_PG_BW_SET(ets->pg_bw_tbl,
				pg_help_data->data[entry_joined].pg, pg_joined);
		}
		/* Joined the entries */
		pg_help_data->num_of_pg--;
	}

	return 0;
}