#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct elf_backend_data {int /*<<< orphan*/  (* elf_backend_grok_psinfo ) (int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/  (* elf_backend_grok_prstatus ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {int alignment_power; int /*<<< orphan*/  filepos; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_16__ {int type; int namesz; int /*<<< orphan*/  descpos; int /*<<< orphan*/  descsz; int /*<<< orphan*/  namedata; } ;
typedef  TYPE_2__ Elf_Internal_Note ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  NT_AUXV 137 
#define  NT_FPREGSET 136 
#define  NT_LWPSTATUS 135 
#define  NT_PRPSINFO 134 
#define  NT_PRSTATUS 133 
#define  NT_PRXFPREG 132 
#define  NT_PSINFO 131 
#define  NT_PSTATUS 130 
#define  NT_THRMISC 129 
#define  NT_WIN32PSTATUS 128 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_get_arch_size (int /*<<< orphan*/ *) ; 
 TYPE_1__* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfcore_grok_lwpstatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_prfpreg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_prstatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_prxfpreg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_psinfo (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_pstatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_thrmisc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elfcore_grok_win32pstatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static bfd_boolean
elfcore_grok_note (bfd *abfd, Elf_Internal_Note *note)
{
  const struct elf_backend_data *bed = get_elf_backend_data (abfd);

  switch (note->type)
    {
    default:
      return TRUE;

    case NT_PRSTATUS:
      if (bed->elf_backend_grok_prstatus)
	if ((*bed->elf_backend_grok_prstatus) (abfd, note))
	  return TRUE;
#if defined (HAVE_PRSTATUS_T)
      return elfcore_grok_prstatus (abfd, note);
#else
      return TRUE;
#endif

#if defined (HAVE_PSTATUS_T)
    case NT_PSTATUS:
      return elfcore_grok_pstatus (abfd, note);
#endif

#if defined (HAVE_LWPSTATUS_T)
    case NT_LWPSTATUS:
      return elfcore_grok_lwpstatus (abfd, note);
#endif

    case NT_FPREGSET:		/* FIXME: rename to NT_PRFPREG */
      return elfcore_grok_prfpreg (abfd, note);

#if defined (HAVE_WIN32_PSTATUS_T)
    case NT_WIN32PSTATUS:
      return elfcore_grok_win32pstatus (abfd, note);
#endif

    case NT_PRXFPREG:		/* Linux SSE extension */
      if (note->namesz == 6
	  && strcmp (note->namedata, "LINUX") == 0)
	return elfcore_grok_prxfpreg (abfd, note);
      else
	return TRUE;

    case NT_PRPSINFO:
    case NT_PSINFO:
      if (bed->elf_backend_grok_psinfo)
	if ((*bed->elf_backend_grok_psinfo) (abfd, note))
	  return TRUE;
#if defined (HAVE_PRPSINFO_T) || defined (HAVE_PSINFO_T)
      return elfcore_grok_psinfo (abfd, note);
#else
      return TRUE;
#endif

    case NT_AUXV:
      {
	asection *sect = bfd_make_section_anyway_with_flags (abfd, ".auxv",
							     SEC_HAS_CONTENTS);

	if (sect == NULL)
	  return FALSE;
	sect->size = note->descsz;
	sect->filepos = note->descpos;
	sect->alignment_power = 1 + bfd_get_arch_size (abfd) / 32;

	return TRUE;
      }

#if defined (HAVE_THRMISC_T)
    case NT_THRMISC:
      return elfcore_grok_thrmisc (abfd, note);
#endif

    }
}