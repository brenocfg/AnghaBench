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
struct niter_desc {int dummy; } ;
struct loop {int /*<<< orphan*/ * aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct niter_desc*) ; 
 struct niter_desc* simple_loop_desc (struct loop*) ; 

void
free_simple_loop_desc (struct loop *loop)
{
  struct niter_desc *desc = simple_loop_desc (loop);

  if (!desc)
    return;

  free (desc);
  loop->aux = NULL;
}