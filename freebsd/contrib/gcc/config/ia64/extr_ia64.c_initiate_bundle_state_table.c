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
typedef  int /*<<< orphan*/  htab_del ;

/* Variables and functions */
 int /*<<< orphan*/  bundle_state_eq_p ; 
 int /*<<< orphan*/  bundle_state_hash ; 
 int /*<<< orphan*/  bundle_state_table ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initiate_bundle_state_table (void)
{
  bundle_state_table = htab_create (50, bundle_state_hash, bundle_state_eq_p,
				    (htab_del) 0);
}