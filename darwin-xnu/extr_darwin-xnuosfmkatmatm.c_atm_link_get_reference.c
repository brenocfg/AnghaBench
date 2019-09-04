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
typedef  int /*<<< orphan*/  atm_link_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  atm_link_object_reference_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atm_link_get_reference(atm_link_object_t link_object)
{
	atm_link_object_reference_internal(link_object);
}