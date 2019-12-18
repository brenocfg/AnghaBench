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
typedef  int /*<<< orphan*/  dtrace_stmt_f ;
typedef  int /*<<< orphan*/  dtrace_ecbdesc_t ;
struct TYPE_3__ {int /*<<< orphan*/  dc_prog; } ;
typedef  TYPE_1__ dtrace_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_stmt_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_dtp ; 
 scalar_t__ list_stmt ; 

__attribute__((used)) static void
list_prog(const dtrace_cmd_t *dcp)
{
	dtrace_ecbdesc_t *last = NULL;

	(void) dtrace_stmt_iter(g_dtp, dcp->dc_prog,
	    (dtrace_stmt_f *)list_stmt, &last);
}