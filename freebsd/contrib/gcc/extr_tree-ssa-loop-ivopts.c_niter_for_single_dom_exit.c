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
typedef  int /*<<< orphan*/ * tree ;
struct ivopts_data {int /*<<< orphan*/  current_loop; } ;
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/ * niter_for_exit (struct ivopts_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_dom_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
niter_for_single_dom_exit (struct ivopts_data *data)
{
  edge exit = single_dom_exit (data->current_loop);

  if (!exit)
    return NULL;

  return niter_for_exit (data, exit);
}