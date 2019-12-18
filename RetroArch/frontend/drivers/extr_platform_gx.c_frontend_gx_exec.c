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
 int /*<<< orphan*/  system_exec_wii (char const*,int) ; 

__attribute__((used)) static void frontend_gx_exec(const char *path, bool should_load_game)
{
#ifdef HW_RVL
   system_exec_wii(path, should_load_game);
#endif
}