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
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  disconnect_dest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect_src (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_on_shrinking_pred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_predictions_associated_with_edge (int /*<<< orphan*/ ) ; 

void
remove_edge (edge e)
{
  remove_predictions_associated_with_edge (e);
  execute_on_shrinking_pred (e);

  disconnect_src (e);
  disconnect_dest (e);

  free_edge (e);
}