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
 int /*<<< orphan*/  _sparc_dvma ; 
 int /*<<< orphan*/  proc_create_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sparc_io_proc_fops ; 
 int /*<<< orphan*/  sparc_iomap ; 

__attribute__((used)) static void register_proc_sparc_ioport(void)
{
#ifdef CONFIG_PROC_FS
	proc_create_data("io_map", 0, NULL, &sparc_io_proc_fops, &sparc_iomap);
	proc_create_data("dvma_map", 0, NULL, &sparc_io_proc_fops, &_sparc_dvma);
#endif
}