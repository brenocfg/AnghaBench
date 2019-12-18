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
struct dwarf_expr_baton {int /*<<< orphan*/  objfile; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  target_get_thread_local_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_get_thread_local_address_p () ; 

__attribute__((used)) static CORE_ADDR
dwarf_expr_tls_address (void *baton, CORE_ADDR offset)
{
  struct dwarf_expr_baton *debaton = (struct dwarf_expr_baton *) baton;
  CORE_ADDR addr;

  if (target_get_thread_local_address_p ())
    addr = target_get_thread_local_address (inferior_ptid,
					    debaton->objfile,
					    offset);
  /* It wouldn't be wrong here to try a gdbarch method, too; finding
     TLS is an ABI-specific thing.  But we don't do that yet.  */
  else
    error ("Cannot find thread-local variables on this target");

  return addr;
}