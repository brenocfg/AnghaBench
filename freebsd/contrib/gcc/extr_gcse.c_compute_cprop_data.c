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
 int /*<<< orphan*/  compute_available (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_local_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cprop_absaltered ; 
 int /*<<< orphan*/  cprop_avin ; 
 int /*<<< orphan*/  cprop_avout ; 
 int /*<<< orphan*/  cprop_pavloc ; 
 int /*<<< orphan*/  set_hash_table ; 

__attribute__((used)) static void
compute_cprop_data (void)
{
  compute_local_properties (cprop_absaltered, cprop_pavloc, NULL, &set_hash_table);
  compute_available (cprop_pavloc, cprop_absaltered,
		     cprop_avout, cprop_avin);
}