#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ link; } ;
struct TYPE_6__ {TYPE_1__ i; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; TYPE_3__ root; } ;
struct collect_gnu_hash_codes {int min_dynindx; unsigned long* hashval; unsigned long bucketcount; int shift1; int maskbits; int* bitmask; int mask; int shift2; int* counts; int* indx; int symindx; scalar_t__ contents; int /*<<< orphan*/  output_bfd; int /*<<< orphan*/  local_indx; TYPE_4__* bed; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_8__ {int /*<<< orphan*/  (* elf_hash_symbol ) (struct elf_link_hash_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct elf_link_hash_entry*) ; 

__attribute__((used)) static bfd_boolean
elf_renumber_gnu_hash_syms (struct elf_link_hash_entry *h, void *data)
{
  struct collect_gnu_hash_codes *s = data;
  unsigned long int bucket;
  unsigned long int val;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  /* Ignore indirect symbols.  */
  if (h->dynindx == -1)
    return TRUE;

  /* Ignore also local symbols and undefined symbols.  */
  if (! (*s->bed->elf_hash_symbol) (h))
    {
      if (h->dynindx >= s->min_dynindx)
	h->dynindx = s->local_indx++;
      return TRUE;
    }

  bucket = s->hashval[h->dynindx] % s->bucketcount;
  val = (s->hashval[h->dynindx] >> s->shift1)
	& ((s->maskbits >> s->shift1) - 1);
  s->bitmask[val] |= ((bfd_vma) 1) << (s->hashval[h->dynindx] & s->mask);
  s->bitmask[val]
    |= ((bfd_vma) 1) << ((s->hashval[h->dynindx] >> s->shift2) & s->mask);
  val = s->hashval[h->dynindx] & ~(unsigned long int) 1;
  if (s->counts[bucket] == 1)
    /* Last element terminates the chain.  */
    val |= 1;
  bfd_put_32 (s->output_bfd, val,
	      s->contents + (s->indx[bucket] - s->symindx) * 4);
  --s->counts[bucket];
  h->dynindx = s->indx[bucket]++;
  return TRUE;
}