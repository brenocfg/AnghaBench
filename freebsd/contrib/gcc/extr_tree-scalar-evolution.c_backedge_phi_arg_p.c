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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int EDGE_IRREDUCIBLE_LOOP ; 
 TYPE_1__* PHI_ARG_EDGE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
backedge_phi_arg_p (tree phi, int i)
{
  edge e = PHI_ARG_EDGE (phi, i);

  /* We would in fact like to test EDGE_DFS_BACK here, but we do not care
     about updating it anywhere, and this should work as well most of the
     time.  */
  if (e->flags & EDGE_IRREDUCIBLE_LOOP)
    return true;

  return false;
}