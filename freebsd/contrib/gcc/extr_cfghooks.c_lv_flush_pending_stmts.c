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
struct TYPE_2__ {int /*<<< orphan*/  (* flush_pending_stmts ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* cfg_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
lv_flush_pending_stmts (edge e)
{
  if (cfg_hooks->flush_pending_stmts)
    cfg_hooks->flush_pending_stmts (e);
}