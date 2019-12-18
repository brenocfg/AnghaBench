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
 int /*<<< orphan*/  RARCH_DIR_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_DIR_SAVESTATE ; 
 int /*<<< orphan*/  RARCH_DIR_SYSTEM ; 
 int /*<<< orphan*/  dir_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dir_clear_all(void)
{
   dir_clear(RARCH_DIR_SYSTEM);
   dir_clear(RARCH_DIR_SAVEFILE);
   dir_clear(RARCH_DIR_SAVESTATE);
}