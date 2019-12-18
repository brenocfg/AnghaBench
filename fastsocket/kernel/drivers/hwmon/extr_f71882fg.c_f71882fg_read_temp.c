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
typedef  int /*<<< orphan*/  u16 ;
struct f71882fg_data {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  F71882FG_REG_TEMP (int) ; 
 scalar_t__ f71858fg ; 
 int /*<<< orphan*/  f71882fg_read16 (struct f71882fg_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71882fg_read8 (struct f71882fg_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 f71882fg_read_temp(struct f71882fg_data *data, int nr)
{
	if (data->type == f71858fg)
		return f71882fg_read16(data, F71882FG_REG_TEMP(nr));
	else
		return f71882fg_read8(data, F71882FG_REG_TEMP(nr));
}