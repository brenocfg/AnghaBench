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
struct property {int deleted; int /*<<< orphan*/  labels; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_labels (int /*<<< orphan*/ *) ; 

void delete_property(struct property *prop)
{
	prop->deleted = 1;
	delete_labels(&prop->labels);
}