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
struct objfile {int dummy; } ;
typedef  enum minimal_symbol_type { ____Placeholder_minimal_symbol_type } minimal_symbol_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  prim_record_minimal_symbol (char*,int /*<<< orphan*/ ,int,struct objfile*) ; 

__attribute__((used)) static void
record_minimal_symbol (char *name, CORE_ADDR address,
		       enum minimal_symbol_type type, struct objfile *objfile)
{
  /* We don't want TDESC entry points in the minimal symbol table */
  if (name[0] == '@')
    return;

  prim_record_minimal_symbol (name, address, type, objfile);
}