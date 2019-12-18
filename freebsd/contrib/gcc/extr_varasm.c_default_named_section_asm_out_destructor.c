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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int DEFAULT_INIT_PRIORITY ; 
 int MAX_INIT_PRIORITY ; 
 int POINTER_SIZE ; 
 int /*<<< orphan*/  SECTION_WRITE ; 
 int /*<<< orphan*/  assemble_align (int) ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  get_section (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 

void
default_named_section_asm_out_destructor (rtx symbol, int priority)
{
  const char *section = ".dtors";
  char buf[16];

  /* ??? This only works reliably with the GNU linker.  */
  if (priority != DEFAULT_INIT_PRIORITY)
    {
      sprintf (buf, ".dtors.%.5u",
	       /* Invert the numbering so the linker puts us in the proper
		  order; constructors are run from right to left, and the
		  linker sorts in increasing order.  */
	       MAX_INIT_PRIORITY - priority);
      section = buf;
    }

  switch_to_section (get_section (section, SECTION_WRITE, NULL));
  assemble_align (POINTER_SIZE);
  assemble_integer (symbol, POINTER_SIZE / BITS_PER_UNIT, POINTER_SIZE, 1);
}