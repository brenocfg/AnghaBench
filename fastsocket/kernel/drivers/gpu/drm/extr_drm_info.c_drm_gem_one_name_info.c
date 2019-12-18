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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct drm_gem_object {TYPE_1__ refcount; int /*<<< orphan*/  handle_count; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_gem_one_name_info(int id, void *ptr, void *data)
{
	struct drm_gem_object *obj = ptr;
	struct seq_file *m = data;

	seq_printf(m, "%6d %8zd %7d %8d\n",
		   obj->name, obj->size,
		   atomic_read(&obj->handle_count),
		   atomic_read(&obj->refcount.refcount));
	return 0;
}