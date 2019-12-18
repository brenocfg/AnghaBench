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
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG_APPEND ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE_OPTIONS ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void path_clear_all(void)
{
   path_clear(RARCH_PATH_CONTENT);
   path_clear(RARCH_PATH_CONFIG);
   path_clear(RARCH_PATH_CONFIG_APPEND);
   path_clear(RARCH_PATH_CORE_OPTIONS);
   path_clear(RARCH_PATH_BASENAME);
}