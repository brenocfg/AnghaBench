#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct so_list {struct so_list* next; } ;
struct objfile {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct breakpoint {int dummy; } ;
struct TYPE_9__ {scalar_t__ start_address; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_11__ {int /*<<< orphan*/  dld_flags; int /*<<< orphan*/  dld_flags_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  obfd; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DT_HP_DEBUG_CALLBACK ; 
 int /*<<< orphan*/  DT_HP_DEBUG_PRIVATE ; 
 char* alloca (unsigned int) ; 
 int /*<<< orphan*/  bfd_check_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (TYPE_1__*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ bfd_lookup_symbol (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_1__* bfd_openr (char*,int /*<<< orphan*/ ) ; 
 unsigned int bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_symtab_users () ; 
 struct breakpoint* create_solib_event_breakpoint (scalar_t__) ; 
 TYPE_3__ dld_cache ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  make_breakpoint_permanent (struct breakpoint*) ; 
 int /*<<< orphan*/  read_dynamic_info (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ read_pc () ; 
 int /*<<< orphan*/  remove_solib_event_breakpoints () ; 
 struct so_list* so_list_head ; 
 TYPE_2__* symfile_objfile ; 
 unsigned int target_write_memory (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 
 int /*<<< orphan*/  xfree (struct so_list*) ; 

void
pa64_solib_create_inferior_hook (void)
{
  struct minimal_symbol *msymbol;
  unsigned int dld_flags, status;
  asection *shlib_info, *interp_sect;
  char buf[4];
  struct objfile *objfile;
  CORE_ADDR anaddr;

  /* First, remove all the solib event breakpoints.  Their addresses
     may have changed since the last time we ran the program.  */
  remove_solib_event_breakpoints ();

  if (symfile_objfile == NULL)
    return;

  /* First see if the objfile was dynamically linked.  */
  shlib_info = bfd_get_section_by_name (symfile_objfile->obfd, ".dynamic");
  if (!shlib_info)
    return;

  /* It's got a .dynamic section, make sure it's not empty.  */
  if (bfd_section_size (symfile_objfile->obfd, shlib_info) == 0)
    return;

  /* Read in the .dynamic section.  */
  if (! read_dynamic_info (shlib_info, &dld_cache))
    error ("Unable to read the .dynamic section.");

  /* Turn on the flags we care about.  */
  dld_cache.dld_flags |= DT_HP_DEBUG_PRIVATE;
  dld_cache.dld_flags |= DT_HP_DEBUG_CALLBACK;
  status = target_write_memory (dld_cache.dld_flags_addr,
				(char *) &dld_cache.dld_flags,
				sizeof (dld_cache.dld_flags));
  if (status != 0)
    error ("Unable to modify dynamic linker flags.");

  /* Now we have to create a shared library breakpoint in the dynamic
     linker.  This can be somewhat tricky since the symbol is inside
     the dynamic linker (for which we do not have symbols or a base
     load address!   Luckily I wrote this code for solib.c years ago.  */
  interp_sect = bfd_get_section_by_name (exec_bfd, ".interp");
  if (interp_sect)
    {
      unsigned int interp_sect_size;
      char *buf;
      CORE_ADDR load_addr;
      bfd *tmp_bfd;
      CORE_ADDR sym_addr = 0;

      /* Read the contents of the .interp section into a local buffer;
	 the contents specify the dynamic linker this program uses.  */
      interp_sect_size = bfd_section_size (exec_bfd, interp_sect);
      buf = alloca (interp_sect_size);
      bfd_get_section_contents (exec_bfd, interp_sect,
				buf, 0, interp_sect_size);

      /* Now we need to figure out where the dynamic linker was
	 loaded so that we can load its symbols and place a breakpoint
	 in the dynamic linker itself.

	 This address is stored on the stack.  However, I've been unable
	 to find any magic formula to find it for Solaris (appears to
	 be trivial on GNU/Linux).  Therefore, we have to try an alternate
	 mechanism to find the dynamic linker's base address.  */
      tmp_bfd = bfd_openr (buf, gnutarget);
      if (tmp_bfd == NULL)
	goto get_out;

      /* Make sure the dynamic linker's really a useful object.  */
      if (!bfd_check_format (tmp_bfd, bfd_object))
	{
	  warning ("Unable to grok dynamic linker %s as an object file", buf);
	  bfd_close (tmp_bfd);
	  goto get_out;
	}

      /* We find the dynamic linker's base address by examining the
	 current pc (which point at the entry point for the dynamic
	 linker) and subtracting the offset of the entry point. 

	 Also note the breakpoint is the second instruction in the
	 routine.  */
      load_addr = read_pc () - tmp_bfd->start_address;
      sym_addr = bfd_lookup_symbol (tmp_bfd, "__dld_break");
      sym_addr = load_addr + sym_addr + 4;
      
      /* Create the shared library breakpoint.  */
      {
	struct breakpoint *b
	  = create_solib_event_breakpoint (sym_addr);

	/* The breakpoint is actually hard-coded into the dynamic linker,
	   so we don't need to actually insert a breakpoint instruction
	   there.  In fact, the dynamic linker's code is immutable, even to
	   ttrace, so we shouldn't even try to do that.  For cases like
	   this, we have "permanent" breakpoints.  */
	make_breakpoint_permanent (b);
      }

      /* We're done with the temporary bfd.  */
      bfd_close (tmp_bfd);
    }

get_out:
  /* Wipe out all knowledge of old shared libraries since their
     mapping can change from one exec to another!  */
  while (so_list_head)
    {
      struct so_list *temp;

      temp = so_list_head;
      xfree (so_list_head);
      so_list_head = temp->next;
    }
  clear_symtab_users ();
}