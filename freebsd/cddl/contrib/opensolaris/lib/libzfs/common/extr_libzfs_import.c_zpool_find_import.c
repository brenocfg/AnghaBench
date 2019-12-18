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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_3__ {int paths; char** path; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ importargs_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zpool_find_import_impl (int /*<<< orphan*/ *,TYPE_1__*) ; 

nvlist_t *
zpool_find_import(libzfs_handle_t *hdl, int argc, char **argv)
{
	importargs_t iarg = { 0 };

	iarg.paths = argc;
	iarg.path = argv;

	return (zpool_find_import_impl(hdl, &iarg));
}