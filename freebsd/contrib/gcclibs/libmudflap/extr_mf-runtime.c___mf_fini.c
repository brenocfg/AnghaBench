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
struct TYPE_2__ {int /*<<< orphan*/  mudflap_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__ __mf_opts ; 
 int /*<<< orphan*/  __mfu_report () ; 
 int /*<<< orphan*/  mode_nop ; 

void __mf_fini ()
{
  TRACE ("__mf_fini\n");
  __mfu_report ();

#ifndef PIC
/* Since we didn't populate the tree for allocations in constructors
   before __mf_init, we cannot check destructors after __mf_fini.  */
  __mf_opts.mudflap_mode = mode_nop;
#endif
}