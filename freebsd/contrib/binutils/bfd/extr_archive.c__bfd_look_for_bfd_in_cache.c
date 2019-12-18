#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ar_cache {int /*<<< orphan*/ * arbfd; int /*<<< orphan*/  ptr; } ;
typedef  scalar_t__ htab_t ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {scalar_t__ cache; } ;

/* Variables and functions */
 TYPE_1__* bfd_ardata (int /*<<< orphan*/ *) ; 
 scalar_t__ htab_find (scalar_t__,struct ar_cache*) ; 

bfd *
_bfd_look_for_bfd_in_cache (bfd *arch_bfd, file_ptr filepos)
{
  htab_t hash_table = bfd_ardata (arch_bfd)->cache;
  struct ar_cache m;
  m.ptr = filepos;

  if (hash_table)
    {
      struct ar_cache *entry = (struct ar_cache *) htab_find (hash_table, &m);
      if (!entry)
	return NULL;
      else
	return entry->arbfd;
    }
  else
    return NULL;
}