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
typedef  int /*<<< orphan*/  const* tree ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 int /*<<< orphan*/  pedwarn (char*,...) ; 

__attribute__((used)) static void
identify_goto (tree decl, const location_t *locus)
{
  if (decl)
    pedwarn ("jump to label %qD", decl);
  else
    pedwarn ("jump to case label");
  if (locus)
    pedwarn ("%H  from here", locus);
}