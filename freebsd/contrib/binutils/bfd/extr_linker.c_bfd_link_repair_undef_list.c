#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_hash_table {struct bfd_link_hash_entry* undefs_tail; struct bfd_link_hash_entry* undefs; } ;
struct TYPE_3__ {struct bfd_link_hash_entry* next; } ;
struct TYPE_4__ {TYPE_1__ undef; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefweak ; 

void
bfd_link_repair_undef_list (struct bfd_link_hash_table *table)
{
  struct bfd_link_hash_entry **pun;

  pun = &table->undefs;
  while (*pun != NULL)
    {
      struct bfd_link_hash_entry *h = *pun;

      if (h->type == bfd_link_hash_new
	  || h->type == bfd_link_hash_undefweak)
	{
	  *pun = h->u.undef.next;
	  h->u.undef.next = NULL;
	  if (h == table->undefs_tail)
	    {
	      if (pun == &table->undefs)
		table->undefs_tail = NULL;
	      else
		/* pun points at an u.undef.next field.  Go back to
		   the start of the link_hash_entry.  */
		table->undefs_tail = (struct bfd_link_hash_entry *)
		  ((char *) pun - ((char *) &h->u.undef.next - (char *) h));
	      break;
	    }
	}
      else
	pun = &h->u.undef.next;
    }
}