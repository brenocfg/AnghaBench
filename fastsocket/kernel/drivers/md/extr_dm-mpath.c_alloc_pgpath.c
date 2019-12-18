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
struct pgpath {int is_active; int /*<<< orphan*/  activate_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activate_path ; 
 struct pgpath* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pgpath *alloc_pgpath(void)
{
	struct pgpath *pgpath = kzalloc(sizeof(*pgpath), GFP_KERNEL);

	if (pgpath) {
		pgpath->is_active = 1;
		INIT_DELAYED_WORK(&pgpath->activate_path, activate_path);
	}

	return pgpath;
}