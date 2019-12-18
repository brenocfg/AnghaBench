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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  pretty_printer ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  INDENT (int) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  PHI_RESULT (scalar_t__) ; 
 int TDF_VOPS ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,scalar_t__,int,int,int) ; 
 scalar_t__ is_gimple_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
dump_phi_nodes (pretty_printer *buffer, basic_block bb, int indent, int flags)
{
  tree phi = phi_nodes (bb);
  if (!phi)
    return;

  for (; phi; phi = PHI_CHAIN (phi))
    {
      if (is_gimple_reg (PHI_RESULT (phi)) || (flags & TDF_VOPS))
        {
          INDENT (indent);
          pp_string (buffer, "# ");
          dump_generic_node (buffer, phi, indent, flags, false);
          pp_newline (buffer);
        }
    }
}