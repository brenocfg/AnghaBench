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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pname ; 

__attribute__((used)) static void
usage (void)
{
#ifdef UNPROTOIZE
  notice ("%s: usage '%s [ -VqfnkN ] [ -i <istring> ] [ filename ... ]'\n",
	  pname, pname);
#else /* !defined (UNPROTOIZE) */
  notice ("%s: usage '%s [ -VqfnkNlgC ] [ -B <dirname> ] [ filename ... ]'\n",
	  pname, pname);
#endif /* !defined (UNPROTOIZE) */
  exit (FATAL_EXIT_CODE);
}