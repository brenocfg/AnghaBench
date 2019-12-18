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
struct _Unwind_Exception {int /*<<< orphan*/  (* exception_cleanup ) (int /*<<< orphan*/ ,struct _Unwind_Exception*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _URC_FOREIGN_EXCEPTION_CAUGHT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct _Unwind_Exception*) ; 

void
_Unwind_DeleteException (struct _Unwind_Exception *exc)
{
  if (exc->exception_cleanup)
    (*exc->exception_cleanup) (_URC_FOREIGN_EXCEPTION_CAUGHT, exc);
}