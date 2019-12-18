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
typedef  int /*<<< orphan*/  zpool_iter_f ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */

int zpool_iter(libzfs_handle_t* handle, zpool_iter_f iter, void* arg) {
	return (0);
}