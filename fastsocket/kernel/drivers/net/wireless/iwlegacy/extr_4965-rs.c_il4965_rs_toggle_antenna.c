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
typedef  size_t u32 ;
struct il_scale_tbl_info {size_t ant_type; } ;

/* Variables and functions */
 size_t ANT_ABC ; 
 size_t RATE_MCS_ANT_ABC_MSK ; 
 size_t RATE_MCS_ANT_POS ; 
 size_t* ant_toggle_lookup ; 
 int /*<<< orphan*/  il4965_rs_is_valid_ant (size_t,size_t) ; 

__attribute__((used)) static int
il4965_rs_toggle_antenna(u32 valid_ant, u32 *rate_n_flags,
			 struct il_scale_tbl_info *tbl)
{
	u8 new_ant_type;

	if (!tbl->ant_type || tbl->ant_type > ANT_ABC)
		return 0;

	if (!il4965_rs_is_valid_ant(valid_ant, tbl->ant_type))
		return 0;

	new_ant_type = ant_toggle_lookup[tbl->ant_type];

	while (new_ant_type != tbl->ant_type &&
	       !il4965_rs_is_valid_ant(valid_ant, new_ant_type))
		new_ant_type = ant_toggle_lookup[new_ant_type];

	if (new_ant_type == tbl->ant_type)
		return 0;

	tbl->ant_type = new_ant_type;
	*rate_n_flags &= ~RATE_MCS_ANT_ABC_MSK;
	*rate_n_flags |= new_ant_type << RATE_MCS_ANT_POS;
	return 1;
}