#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct spu_link_hash_table {unsigned int num_overlays; unsigned int num_buf; TYPE_2__** ovl_region; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_11__ {int section_count; TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_12__ {int flags; scalar_t__ size; scalar_t__ vma; struct TYPE_12__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_13__ {unsigned int ovl_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_LOAD ; 
 int SEC_THREAD_LOCAL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__** bfd_malloc (int) ; 
 TYPE_2__** bfd_realloc (TYPE_2__**,unsigned int) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 int /*<<< orphan*/  qsort (TYPE_2__**,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort_sections ; 
 TYPE_3__* spu_elf_section_data (TYPE_2__*) ; 
 struct spu_link_hash_table* spu_hash_table (struct bfd_link_info*) ; 

bfd_boolean
spu_elf_find_overlays (bfd *output_bfd, struct bfd_link_info *info)
{
  struct spu_link_hash_table *htab = spu_hash_table (info);
  asection **alloc_sec;
  unsigned int i, n, ovl_index, num_buf;
  asection *s;
  bfd_vma ovl_end;

  if (output_bfd->section_count < 2)
    return FALSE;

  alloc_sec = bfd_malloc (output_bfd->section_count * sizeof (*alloc_sec));
  if (alloc_sec == NULL)
    return FALSE;

  /* Pick out all the alloced sections.  */
  for (n = 0, s = output_bfd->sections; s != NULL; s = s->next)
    if ((s->flags & SEC_ALLOC) != 0
	&& (s->flags & (SEC_LOAD | SEC_THREAD_LOCAL)) != SEC_THREAD_LOCAL
	&& s->size != 0)
      alloc_sec[n++] = s;

  if (n == 0)
    {
      free (alloc_sec);
      return FALSE;
    }

  /* Sort them by vma.  */
  qsort (alloc_sec, n, sizeof (*alloc_sec), sort_sections);

  /* Look for overlapping vmas.  Any with overlap must be overlays.
     Count them.  Also count the number of overlay regions and for
     each region save a section from that region with the lowest vma
     and another section with the highest end vma.  */
  ovl_end = alloc_sec[0]->vma + alloc_sec[0]->size;
  for (ovl_index = 0, num_buf = 0, i = 1; i < n; i++)
    {
      s = alloc_sec[i];
      if (s->vma < ovl_end)
	{
	  asection *s0 = alloc_sec[i - 1];

	  if (spu_elf_section_data (s0)->ovl_index == 0)
	    {
	      spu_elf_section_data (s0)->ovl_index = ++ovl_index;
	      alloc_sec[num_buf * 2] = s0;
	      alloc_sec[num_buf * 2 + 1] = s0;
	      num_buf++;
	    }
	  spu_elf_section_data (s)->ovl_index = ++ovl_index;
	  if (ovl_end < s->vma + s->size)
	    {
	      ovl_end = s->vma + s->size;
	      alloc_sec[num_buf * 2 - 1] = s;
	    }
	}
      else
	ovl_end = s->vma + s->size;
    }

  htab->num_overlays = ovl_index;
  htab->num_buf = num_buf;
  if (ovl_index == 0)
    {
      free (alloc_sec);
      return FALSE;
    }

  alloc_sec = bfd_realloc (alloc_sec, num_buf * 2 * sizeof (*alloc_sec));
  if (alloc_sec == NULL)
    return FALSE;

  htab->ovl_region = alloc_sec;
  return TRUE;
}