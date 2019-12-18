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
struct api_info {scalar_t__ refcnt; scalar_t__ minor; scalar_t__ major; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  sun4v_set_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void __put_ref(struct api_info *p)
{
	if (--p->refcnt == 0) {
		unsigned long ignore;

		sun4v_set_version(p->group, 0, 0, &ignore);
		p->major = p->minor = 0;
	}
}