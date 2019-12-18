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
struct TYPE_3__ {scalar_t__ namesz; char* namedata; int /*<<< orphan*/  descsz; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Elf_Internal_Note ;

/* Variables and functions */
 scalar_t__ const_strneq (char*,char*) ; 
 char* get_freebsd_note_type (int /*<<< orphan*/ ) ; 
 char* get_gnu_note_type (int /*<<< orphan*/ ) ; 
 char* get_netbsd_elfcore_note_type (int /*<<< orphan*/ ) ; 
 char* get_note_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
process_note (Elf_Internal_Note *pnote)
{
  const char *nt;

  if (pnote->namesz == 0)
    /* If there is no note name, then use the default set of
       note type strings.  */
    nt = get_note_type (pnote->type);

  else if (const_strneq (pnote->namedata, "FreeBSD"))
    /* FreeBSD-specific core file notes.  */
    nt = get_freebsd_note_type (pnote->type);

  else if (const_strneq (pnote->namedata, "GNU"))
    /* GNU-specific notes */
    nt = get_gnu_note_type (pnote->type);

  else if (const_strneq (pnote->namedata, "NetBSD-CORE"))
    /* NetBSD-specific core file notes.  */
    nt = get_netbsd_elfcore_note_type (pnote->type);

  else
    /* Don't recognize this note name; just use the default set of
       note type strings.  */
      nt = get_note_type (pnote->type);

  printf ("  %-13s 0x%08lx\t%s\n",
	  pnote->namesz ? pnote->namedata : "(NONE)",
	  pnote->descsz, nt);
  return 1;
}