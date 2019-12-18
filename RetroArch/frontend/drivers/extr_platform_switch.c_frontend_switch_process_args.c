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
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 

void frontend_switch_process_args(int *argc, char *argv[])
{
#ifdef HAVE_STATIC_DUMMY
   if (*argc >= 1)
   {
      /* Ensure current Path is set, only works for the static dummy, likely a hbloader args Issue (?) */
      path_set(RARCH_PATH_CORE, argv[0]);
   }
#endif
}