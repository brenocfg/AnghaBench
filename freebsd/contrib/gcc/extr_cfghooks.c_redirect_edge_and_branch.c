#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int /*<<< orphan*/  (* redirect_edge_and_branch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* cfg_hooks ; 
 int /*<<< orphan*/  internal_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

edge
redirect_edge_and_branch (edge e, basic_block dest)
{
  edge ret;

  if (!cfg_hooks->redirect_edge_and_branch)
    internal_error ("%s does not support redirect_edge_and_branch",
		    cfg_hooks->name);

  ret = cfg_hooks->redirect_edge_and_branch (e, dest);

  return ret;
}