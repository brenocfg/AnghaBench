#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* get_proc_address ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_LOG_ERROR ; 
 TYPE_1__ hw_render ; 
 int /*<<< orphan*/  log_cb (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ stub1 (char const*) ; 

__attribute__((used)) static void *get_proc_address_mpv(void *fn_ctx, const char *name)
{
	/* The "ISO C forbids conversion of function pointer to object pointer
	 * type" warning is suppressed.
	 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
	void *proc_addr = (void *) hw_render.get_proc_address(name);
#pragma GCC diagnostic pop

	if(proc_addr == NULL)
		log_cb(RETRO_LOG_ERROR, "Failure obtaining %s proc address\n", name);

	return proc_addr;
}