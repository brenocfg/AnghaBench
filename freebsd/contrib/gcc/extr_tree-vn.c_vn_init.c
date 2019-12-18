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
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shared_lookup_vuses ; 
 int /*<<< orphan*/  val_expr_pair_expr_eq ; 
 int /*<<< orphan*/  val_expr_pair_hash ; 
 int /*<<< orphan*/  value_table ; 

void
vn_init (void)
{
  value_table = htab_create (511, val_expr_pair_hash,
			     val_expr_pair_expr_eq, free);
  shared_lookup_vuses = NULL;
}