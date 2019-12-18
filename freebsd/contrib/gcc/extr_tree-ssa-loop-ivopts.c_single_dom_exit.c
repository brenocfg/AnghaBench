#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct loop {TYPE_1__* single_exit; } ;
typedef  TYPE_1__* edge ;
struct TYPE_3__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  just_once_each_iteration_p (struct loop*,int /*<<< orphan*/ ) ; 

edge
single_dom_exit (struct loop *loop)
{
  edge exit = loop->single_exit;

  if (!exit)
    return NULL;

  if (!just_once_each_iteration_p (loop, exit->src))
    return NULL;

  return exit;
}