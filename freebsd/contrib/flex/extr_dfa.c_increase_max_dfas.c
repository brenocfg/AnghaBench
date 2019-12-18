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
 scalar_t__ MAX_DFAS_INCREMENT ; 
 scalar_t__ accsiz ; 
 scalar_t__ base ; 
 int /*<<< orphan*/  current_max_dfas ; 
 scalar_t__ def ; 
 int /*<<< orphan*/  dfaacc ; 
 scalar_t__ dfasiz ; 
 scalar_t__ dhash ; 
 int /*<<< orphan*/  dss ; 
 scalar_t__ nultrans ; 
 int /*<<< orphan*/  num_reallocs ; 
 int /*<<< orphan*/  reallocate_dfaacc_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reallocate_int_ptr_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reallocate_integer_array (scalar_t__,int /*<<< orphan*/ ) ; 

void increase_max_dfas ()
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++num_reallocs;

	base = reallocate_integer_array (base, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_dfaacc_union (dfaacc, current_max_dfas);

	if (nultrans)
		nultrans =
			reallocate_integer_array (nultrans,
						  current_max_dfas);
}