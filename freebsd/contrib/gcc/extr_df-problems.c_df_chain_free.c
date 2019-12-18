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
struct dataflow {int /*<<< orphan*/  block_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dataflow*) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
df_chain_free (struct dataflow *dflow)
{
  free_alloc_pool (dflow->block_pool);
  free (dflow);
}