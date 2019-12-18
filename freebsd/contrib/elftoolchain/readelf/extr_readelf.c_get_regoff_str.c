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
struct readelf {int dummy; } ;
typedef  int /*<<< orphan*/  rs ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ Dwarf_Half ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 scalar_t__ DW_FRAME_CFA_COL ; 
 scalar_t__ DW_FRAME_REG_INITIAL_VALUE ; 
 scalar_t__ DW_FRAME_UNDEFINED_VAL ; 
 char* dwarf_regname (struct readelf*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static char *
get_regoff_str(struct readelf *re, Dwarf_Half reg, Dwarf_Addr off)
{
	static char rs[16];

	if (reg == DW_FRAME_UNDEFINED_VAL || reg == DW_FRAME_REG_INITIAL_VALUE)
		snprintf(rs, sizeof(rs), "%c", 'u');
	else if (reg == DW_FRAME_CFA_COL)
		snprintf(rs, sizeof(rs), "c%+jd", (intmax_t) off);
	else
		snprintf(rs, sizeof(rs), "%s%+jd", dwarf_regname(re, reg),
		    (intmax_t) off);

	return (rs);
}