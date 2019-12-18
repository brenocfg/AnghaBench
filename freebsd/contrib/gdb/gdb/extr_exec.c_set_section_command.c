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
struct section_table {unsigned long addr; long endaddr; int /*<<< orphan*/  the_bfd_section; } ;
typedef  int /*<<< orphan*/  secprint ;
struct TYPE_3__ {struct section_table* to_sections_end; struct section_table* to_sections; } ;

/* Variables and functions */
 char* bfd_section_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  exec_files_info (TYPE_1__*) ; 
 TYPE_1__ exec_ops ; 
 int /*<<< orphan*/  isspace (char) ; 
 unsigned long parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,unsigned int) ; 

__attribute__((used)) static void
set_section_command (char *args, int from_tty)
{
  struct section_table *p;
  char *secname;
  unsigned seclen;
  unsigned long secaddr;
  char secprint[100];
  long offset;

  if (args == 0)
    error ("Must specify section name and its virtual address");

  /* Parse out section name */
  for (secname = args; !isspace (*args); args++);
  seclen = args - secname;

  /* Parse out new virtual address */
  secaddr = parse_and_eval_address (args);

  for (p = exec_ops.to_sections; p < exec_ops.to_sections_end; p++)
    {
      if (!strncmp (secname, bfd_section_name (exec_bfd, p->the_bfd_section), seclen)
	  && bfd_section_name (exec_bfd, p->the_bfd_section)[seclen] == '\0')
	{
	  offset = secaddr - p->addr;
	  p->addr += offset;
	  p->endaddr += offset;
	  if (from_tty)
	    exec_files_info (&exec_ops);
	  return;
	}
    }
  if (seclen >= sizeof (secprint))
    seclen = sizeof (secprint) - 1;
  strncpy (secprint, secname, seclen);
  secprint[seclen] = '\0';
  error ("Section %s not found", secprint);
}