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

/* Variables and functions */
 int /*<<< orphan*/  address_space_name_to_int (char*) ; 
 int /*<<< orphan*/  push_type_int (int /*<<< orphan*/ ) ; 

void
push_type_address_space (char *string)
{
  push_type_int (address_space_name_to_int (string));
}