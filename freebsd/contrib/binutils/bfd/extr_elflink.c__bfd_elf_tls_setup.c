#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfd_section {int flags; unsigned int alignment_power; struct bfd_section* next; } ;
struct bfd_link_info {int dummy; } ;
struct TYPE_4__ {struct bfd_section* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_5__ {struct bfd_section* tls_sec; } ;

/* Variables and functions */
 int SEC_THREAD_LOCAL ; 
 TYPE_2__* elf_hash_table (struct bfd_link_info*) ; 

struct bfd_section *
_bfd_elf_tls_setup (bfd *obfd, struct bfd_link_info *info)
{
  struct bfd_section *sec, *tls;
  unsigned int align = 0;

  for (sec = obfd->sections; sec != NULL; sec = sec->next)
    if ((sec->flags & SEC_THREAD_LOCAL) != 0)
      break;
  tls = sec;

  for (; sec != NULL && (sec->flags & SEC_THREAD_LOCAL) != 0; sec = sec->next)
    if (sec->alignment_power > align)
      align = sec->alignment_power;

  elf_hash_table (info)->tls_sec = tls;

  /* Ensure the alignment of the first section is the largest alignment,
     so that the tls segment starts aligned.  */
  if (tls != NULL)
    tls->alignment_power = align;

  return tls;
}