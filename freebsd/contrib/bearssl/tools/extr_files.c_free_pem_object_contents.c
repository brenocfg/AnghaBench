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
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ pem_object ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void
free_pem_object_contents(pem_object *po)
{
	if (po != NULL) {
		xfree(po->name);
		xfree(po->data);
	}
}