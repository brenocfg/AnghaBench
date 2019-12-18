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
typedef  int /*<<< orphan*/  gregset_t ;
typedef  int /*<<< orphan*/  fpregset_t ;
typedef  int /*<<< orphan*/  fpregs ;
typedef  int /*<<< orphan*/  fakename ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int /*<<< orphan*/ * e_ident; } ;
typedef  TYPE_1__ Elf_Internal_Ehdr ;

/* Variables and functions */
 size_t EI_OSABI ; 
 int /*<<< orphan*/  ELFOSABI_FREEBSD ; 
 TYPE_1__* elf_elfheader (int /*<<< orphan*/ *) ; 
 char* elfcore_write_prfpreg (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *,int) ; 
 char* elfcore_write_prpsinfo (int /*<<< orphan*/ *,char*,int*,char*,char*) ; 
 char* elfcore_write_prstatus (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elfcore_write_thrmisc (int /*<<< orphan*/ *,char*,int*,char*,int) ; 
 int /*<<< orphan*/  fill_fpregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_exec_file (int /*<<< orphan*/ ) ; 
 scalar_t__ get_inferior_args () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptid_get_pid (int /*<<< orphan*/ ) ; 
 char* reconcat (char*,char*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_signal ; 
 char* strrchr (scalar_t__,char) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
fbsd_make_corefile_notes (bfd *obfd, int *note_size)
{
  gregset_t gregs;
  fpregset_t fpregs;
  char *note_data = NULL;
  Elf_Internal_Ehdr *i_ehdrp;
  char fakename;

  /* Put a "FreeBSD" label in the ELF header.  */
  i_ehdrp = elf_elfheader (obfd);
  i_ehdrp->e_ident[EI_OSABI] = ELFOSABI_FREEBSD;

  fill_gregset (&gregs, -1);
  note_data = elfcore_write_prstatus (obfd, note_data, note_size,
				      ptid_get_pid (inferior_ptid),
				      stop_signal, &gregs);

  fill_fpregset (&fpregs, -1);
  note_data = elfcore_write_prfpreg (obfd, note_data, note_size,
				     &fpregs, sizeof (fpregs));

  fakename = '\0';
  note_data = elfcore_write_thrmisc (obfd, note_data, note_size,
				     &fakename, sizeof (fakename));

  if (get_exec_file (0))
    {
      char *fname = strrchr (get_exec_file (0), '/') + 1;
      char *psargs = xstrdup (fname);

      if (get_inferior_args ())
	psargs = reconcat (psargs, psargs, " ", get_inferior_args (), NULL);

      note_data = elfcore_write_prpsinfo (obfd, note_data, note_size,
					  fname, psargs);
    }

  make_cleanup (xfree, note_data);
  return note_data;
}