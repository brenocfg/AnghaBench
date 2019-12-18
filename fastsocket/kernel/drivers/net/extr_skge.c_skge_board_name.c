#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skge_hw {int chip_id; } ;
struct TYPE_3__ {int id; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* skge_chips ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *skge_board_name(const struct skge_hw *hw)
{
	int i;
	static char buf[16];

	for (i = 0; i < ARRAY_SIZE(skge_chips); i++)
		if (skge_chips[i].id == hw->chip_id)
			return skge_chips[i].name;

	snprintf(buf, sizeof buf, "chipid 0x%x", hw->chip_id);
	return buf;
}