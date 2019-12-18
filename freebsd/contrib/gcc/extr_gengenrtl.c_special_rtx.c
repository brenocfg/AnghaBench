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
struct TYPE_2__ {int /*<<< orphan*/  enumname; } ;

/* Variables and functions */
 TYPE_1__* defs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
special_rtx (int idx)
{
  return (strcmp (defs[idx].enumname, "CONST_INT") == 0
	  || strcmp (defs[idx].enumname, "REG") == 0
	  || strcmp (defs[idx].enumname, "SUBREG") == 0
	  || strcmp (defs[idx].enumname, "MEM") == 0
	  || strcmp (defs[idx].enumname, "CONST_VECTOR") == 0);
}