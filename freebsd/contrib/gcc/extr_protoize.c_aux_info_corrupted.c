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

/* Variables and functions */
 int /*<<< orphan*/  FATAL_EXIT_CODE ; 
 int /*<<< orphan*/  current_aux_info_lineno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname ; 

__attribute__((used)) static void
aux_info_corrupted (void)
{
  notice ("\n%s: fatal error: aux info file corrupted at line %d\n",
	  pname, current_aux_info_lineno);
  exit (FATAL_EXIT_CODE);
}