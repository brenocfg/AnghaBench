#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct list_info_struct {int dummy; } ;
struct TYPE_7__ {TYPE_2__* frch_last; int /*<<< orphan*/  frch_obstack; } ;
typedef  TYPE_1__ frchainS ;
struct TYPE_8__ {scalar_t__ fr_type; struct TYPE_8__* fr_next; struct list_info_struct* line; int /*<<< orphan*/  fr_line; int /*<<< orphan*/  fr_file; scalar_t__ fr_fix; } ;
typedef  TYPE_2__ fragS ;

/* Variables and functions */
 int /*<<< orphan*/  as_where (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* frag_alloc (int /*<<< orphan*/ *) ; 
 TYPE_2__* frag_now ; 
 scalar_t__ frag_now_fix_octets () ; 
 TYPE_1__* frchain_now ; 
 int /*<<< orphan*/  know (TYPE_1__*) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 

void
frag_new (int old_frags_var_max_size
	  /* Number of chars (already allocated on obstack frags) in
	     variable_length part of frag.  */)
{
  fragS *former_last_fragP;
  frchainS *frchP;

  assert (frchain_now->frch_last == frag_now);

  /* Fix up old frag's fr_fix.  */
  frag_now->fr_fix = frag_now_fix_octets () - old_frags_var_max_size;
  /* Make sure its type is valid.  */
  assert (frag_now->fr_type != 0);

  /* This will align the obstack so the next struct we allocate on it
     will begin at a correct boundary.  */
  (void) obstack_finish (&frchain_now->frch_obstack);
  frchP = frchain_now;
  know (frchP);
  former_last_fragP = frchP->frch_last;
  assert (former_last_fragP != 0);
  assert (former_last_fragP == frag_now);
  frag_now = frag_alloc (&frchP->frch_obstack);

  as_where (&frag_now->fr_file, &frag_now->fr_line);

  /* Generally, frag_now->points to an address rounded up to next
     alignment.  However, characters will add to obstack frags
     IMMEDIATELY after the struct frag, even if they are not starting
     at an alignment address.  */
  former_last_fragP->fr_next = frag_now;
  frchP->frch_last = frag_now;

#ifndef NO_LISTING
  {
    extern struct list_info_struct *listing_tail;
    frag_now->line = listing_tail;
  }
#endif

  assert (frchain_now->frch_last == frag_now);

  frag_now->fr_next = NULL;
}