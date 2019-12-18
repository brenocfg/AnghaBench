#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  d_val; } ;
struct TYPE_12__ {TYPE_2__ d_un; int /*<<< orphan*/  d_tag; } ;
struct TYPE_9__ {scalar_t__ d_val; } ;
struct TYPE_11__ {TYPE_1__ d_un; scalar_t__ d_tag; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ Elf_Internal_Dyn ;
typedef  TYPE_4__ Elf32_External_Dyn ;

/* Variables and functions */
 scalar_t__ BYTE_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_3__* cmalloc (int,int) ; 
 int /*<<< orphan*/  dynamic_addr ; 
 int dynamic_nent ; 
 TYPE_3__* dynamic_section ; 
 int dynamic_size ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_32bit_dynamic_section (FILE *file)
{
  Elf32_External_Dyn *edyn, *ext;
  Elf_Internal_Dyn *entry;

  edyn = get_data (NULL, file, dynamic_addr, 1, dynamic_size,
		   _("dynamic section"));
  if (!edyn)
    return 0;

/* SGI's ELF has more than one section in the DYNAMIC segment, and we
   might not have the luxury of section headers.  Look for the DT_NULL
   terminator to determine the number of entries.  */
  for (ext = edyn, dynamic_nent = 0;
       (char *) ext < (char *) edyn + dynamic_size;
       ext++)
    {
      dynamic_nent++;
      if (BYTE_GET (ext->d_tag) == DT_NULL)
	break;
    }

  dynamic_section = cmalloc (dynamic_nent, sizeof (*entry));
  if (dynamic_section == NULL)
    {
      error (_("Out of memory\n"));
      free (edyn);
      return 0;
    }

  for (ext = edyn, entry = dynamic_section;
       entry < dynamic_section + dynamic_nent;
       ext++, entry++)
    {
      entry->d_tag      = BYTE_GET (ext->d_tag);
      entry->d_un.d_val = BYTE_GET (ext->d_un.d_val);
    }

  free (edyn);

  return 1;
}