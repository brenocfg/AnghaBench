#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Package ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* map_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  package_list ; 
 int /*<<< orphan*/  package_map ; 

void add_package(Package *package) {
    Package *old_package = map_get(&package_map, package->path);
    if (old_package != package) {
        assert(!old_package);
        map_put(&package_map, package->path, package);
        buf_push(package_list, package);
    }
}