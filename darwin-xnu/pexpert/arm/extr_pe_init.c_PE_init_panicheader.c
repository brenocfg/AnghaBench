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
struct embedded_panic_header {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  eph_version; int /*<<< orphan*/  eph_magic; int /*<<< orphan*/  eph_panic_log_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMBEDDED_PANIC_HEADER_CURRENT_VERSION ; 
 int /*<<< orphan*/  EMBEDDED_PANIC_MAGIC ; 
 int /*<<< orphan*/  PE_get_offset_into_panic_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  debug_buf_base ; 
 TYPE_1__* panic_info ; 

void
PE_init_panicheader()
{
	if (!panic_info)
		return;

	bzero(panic_info, sizeof(struct embedded_panic_header));

	/*
	 * The panic log begins immediately after the panic header -- debugger synchronization and other functions
	 * may log into this region before we've become the exclusive panicking CPU and initialize the header here.
	 */
	panic_info->eph_panic_log_offset = PE_get_offset_into_panic_region(debug_buf_base);

	panic_info->eph_magic = EMBEDDED_PANIC_MAGIC;
	panic_info->eph_version = EMBEDDED_PANIC_HEADER_CURRENT_VERSION;

	return;
}