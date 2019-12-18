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

/* Variables and functions */
 int /*<<< orphan*/  PC_DEVELOPMENT_TCP_PORT ; 
 size_t STD_ERR ; 
 size_t STD_OUT ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  dotab_stdout ; 
 int /*<<< orphan*/  wiiu_log_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_logging(void)
{
   wiiu_log_init(PC_DEVELOPMENT_TCP_PORT);
   devoptab_list[STD_OUT] = &dotab_stdout;
   devoptab_list[STD_ERR] = &dotab_stdout;
}