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
struct demangle_data {int /*<<< orphan*/  array_str; int /*<<< orphan*/  vec; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dest_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_str_dest (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dest_demangle_data(struct demangle_data *d)
{

	if (d != NULL) {
		vector_str_dest(&d->arg);
		vector_str_dest(&d->vec);

		dest_cstring(&d->array_str);
	}
}