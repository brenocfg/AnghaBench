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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  INDENT (int) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
newline_and_indent (pretty_printer *buffer, int spc)
{
  pp_newline (buffer);
  INDENT (spc);
}