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
 int /*<<< orphan*/  cmd_log ; 
 int /*<<< orphan*/  dflt_log_category ; 
 int inited ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_cmd_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_platform_init () ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 

void vcos_logging_init(void)
{
   if (inited)
   {
      /* FIXME: should print a warning or something here */
      return;
   }
   vcos_mutex_create(&lock, "vcos_log");

   vcos_log_platform_init();

   vcos_log_register("default", &dflt_log_category);

#if VCOS_WANT_LOG_CMD
   vcos_cmd_register( &cmd_log );
#endif

   vcos_assert(!inited);
   inited = 1;
}