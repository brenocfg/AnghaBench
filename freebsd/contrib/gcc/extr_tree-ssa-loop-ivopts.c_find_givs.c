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
struct loop {unsigned int num_nodes; } ;
struct ivopts_data {struct loop* current_loop; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  find_givs_in_bb (struct ivopts_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body_in_dom_order (struct loop*) ; 

__attribute__((used)) static void
find_givs (struct ivopts_data *data)
{
  struct loop *loop = data->current_loop;
  basic_block *body = get_loop_body_in_dom_order (loop);
  unsigned i;

  for (i = 0; i < loop->num_nodes; i++)
    find_givs_in_bb (data, body[i]);
  free (body);
}