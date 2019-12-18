#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct elf_symbuf_symbol {int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
struct elf_symbuf_head {size_t count; scalar_t__ st_shndx; struct elf_symbuf_symbol* ssym; } ;
typedef  size_t bfd_size_type ;
struct TYPE_6__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_1__ Elf_Internal_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ SHN_UNDEF ; 
 struct elf_symbuf_head* bfd_malloc (size_t) ; 
 TYPE_1__** bfd_malloc2 (size_t,int) ; 
 int /*<<< orphan*/  elf_sort_elf_symbol ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct elf_symbuf_head *
elf_create_symbuf (bfd_size_type symcount, Elf_Internal_Sym *isymbuf)
{
  Elf_Internal_Sym **ind, **indbufend, **indbuf
    = bfd_malloc2 (symcount, sizeof (*indbuf));
  struct elf_symbuf_symbol *ssym;
  struct elf_symbuf_head *ssymbuf, *ssymhead;
  bfd_size_type i, shndx_count;

  if (indbuf == NULL)
    return NULL;

  for (ind = indbuf, i = 0; i < symcount; i++)
    if (isymbuf[i].st_shndx != SHN_UNDEF)
      *ind++ = &isymbuf[i];
  indbufend = ind;

  qsort (indbuf, indbufend - indbuf, sizeof (Elf_Internal_Sym *),
	 elf_sort_elf_symbol);

  shndx_count = 0;
  if (indbufend > indbuf)
    for (ind = indbuf, shndx_count++; ind < indbufend - 1; ind++)
      if (ind[0]->st_shndx != ind[1]->st_shndx)
	shndx_count++;

  ssymbuf = bfd_malloc ((shndx_count + 1) * sizeof (*ssymbuf)
			+ (indbufend - indbuf) * sizeof (*ssym));
  if (ssymbuf == NULL)
    {
      free (indbuf);
      return NULL;
    }

  ssym = (struct elf_symbuf_symbol *) (ssymbuf + shndx_count + 1);
  ssymbuf->ssym = NULL;
  ssymbuf->count = shndx_count;
  ssymbuf->st_shndx = 0;
  for (ssymhead = ssymbuf, ind = indbuf; ind < indbufend; ssym++, ind++)
    {
      if (ind == indbuf || ssymhead->st_shndx != (*ind)->st_shndx)
	{
	  ssymhead++;
	  ssymhead->ssym = ssym;
	  ssymhead->count = 0;
	  ssymhead->st_shndx = (*ind)->st_shndx;
	}
      ssym->st_name = (*ind)->st_name;
      ssym->st_info = (*ind)->st_info;
      ssym->st_other = (*ind)->st_other;
      ssymhead->count++;
    }
  BFD_ASSERT ((bfd_size_type) (ssymhead - ssymbuf) == shndx_count);

  free (indbuf);
  return ssymbuf;
}