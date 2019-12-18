#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rf_q; } ;
typedef  TYPE_1__ rpc_forward ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  rem_que (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fwd_free(rpc_forward *p)
{
  rem_que(&p->rf_q);
  XFREE(p);
}