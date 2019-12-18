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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ shutdown_entry; scalar_t__ shutdown_type; } ;

/* Variables and functions */
 scalar_t__ TB_SHUTDOWN_S3 ; 
 int /*<<< orphan*/  halt () ; 
 int /*<<< orphan*/  switch_to_tboot_pt () ; 
 TYPE_1__* tboot ; 
 int /*<<< orphan*/  tboot_enabled () ; 
 int /*<<< orphan*/  tboot_pg_dir ; 
 scalar_t__ tboot_setup_sleep () ; 

void tboot_shutdown(u32 shutdown_type)
{
	void (*shutdown)(void);

	if (!tboot_enabled())
		return;

	/*
	 * if we're being called before the 1:1 mapping is set up then just
	 * return and let the normal shutdown happen; this should only be
	 * due to very early panic()
	 */
	if (!tboot_pg_dir)
		return;

	/* if this is S3 then set regions to MAC */
	if (shutdown_type == TB_SHUTDOWN_S3)
		if (tboot_setup_sleep())
			return;

	tboot->shutdown_type = shutdown_type;

	switch_to_tboot_pt();

	shutdown = (void(*)(void))(unsigned long)tboot->shutdown_entry;
	shutdown();

	/* should not reach here */
	while (1)
		halt();
}