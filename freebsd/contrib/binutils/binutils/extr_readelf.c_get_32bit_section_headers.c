#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_shoff; } ;
struct TYPE_9__ {int /*<<< orphan*/  sh_entsize; int /*<<< orphan*/  sh_addralign; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_addr; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; } ;
struct TYPE_8__ {void* sh_entsize; void* sh_addralign; void* sh_info; void* sh_link; void* sh_size; void* sh_offset; void* sh_addr; void* sh_flags; void* sh_type; void* sh_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Shdr ;
typedef  TYPE_2__ Elf32_External_Shdr ;

/* Variables and functions */
 void* BYTE_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* cmalloc (unsigned int,int) ; 
 TYPE_6__ elf_header ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* section_headers ; 

__attribute__((used)) static int
get_32bit_section_headers (FILE *file, unsigned int num)
{
  Elf32_External_Shdr *shdrs;
  Elf_Internal_Shdr *internal;
  unsigned int i;

  shdrs = get_data (NULL, file, elf_header.e_shoff,
		    elf_header.e_shentsize, num, _("section headers"));
  if (!shdrs)
    return 0;

  section_headers = cmalloc (num, sizeof (Elf_Internal_Shdr));

  if (section_headers == NULL)
    {
      error (_("Out of memory\n"));
      return 0;
    }

  for (i = 0, internal = section_headers;
       i < num;
       i++, internal++)
    {
      internal->sh_name      = BYTE_GET (shdrs[i].sh_name);
      internal->sh_type      = BYTE_GET (shdrs[i].sh_type);
      internal->sh_flags     = BYTE_GET (shdrs[i].sh_flags);
      internal->sh_addr      = BYTE_GET (shdrs[i].sh_addr);
      internal->sh_offset    = BYTE_GET (shdrs[i].sh_offset);
      internal->sh_size      = BYTE_GET (shdrs[i].sh_size);
      internal->sh_link      = BYTE_GET (shdrs[i].sh_link);
      internal->sh_info      = BYTE_GET (shdrs[i].sh_info);
      internal->sh_addralign = BYTE_GET (shdrs[i].sh_addralign);
      internal->sh_entsize   = BYTE_GET (shdrs[i].sh_entsize);
    }

  free (shdrs);

  return 1;
}