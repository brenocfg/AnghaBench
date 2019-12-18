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
struct TYPE_3__ {int reloc_count; int /*<<< orphan*/  flags; scalar_t__* orelocation; scalar_t__ relocation; } ;
typedef  TYPE_1__ asection ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_RELOC ; 
 int relcount ; 
 int relsize ; 
 scalar_t__ reltab ; 
 scalar_t__* xmalloc (int) ; 

__attribute__((used)) static void
save_relocs (asection *sec)
{
  int i;

  sec->relocation = reltab;
  sec->reloc_count = relcount;
  sec->orelocation = xmalloc ((relcount + 1) * sizeof (arelent *));
  for (i = 0; i < relcount; i++)
    sec->orelocation[i] = sec->relocation + i;
  sec->orelocation[relcount] = 0;
  sec->flags |= SEC_RELOC;
  reltab = 0;
  relcount = relsize = 0;
}