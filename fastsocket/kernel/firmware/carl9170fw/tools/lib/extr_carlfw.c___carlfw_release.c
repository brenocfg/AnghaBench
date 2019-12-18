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
struct carlfw_file {int /*<<< orphan*/ * data; int /*<<< orphan*/ * name; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __carlfw_release(struct carlfw_file *f)
{
	f->len = 0;
	if (f->name)
		free(f->name);
	f->name = NULL;

	if (f->data)
		free(f->data);
	f->data = NULL;
}