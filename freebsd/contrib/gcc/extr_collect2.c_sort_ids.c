#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct id {scalar_t__ sequence; struct id* next; int /*<<< orphan*/  name; } ;
struct head {struct id* first; } ;

/* Variables and functions */
 scalar_t__ extract_init_priority (int /*<<< orphan*/ ) ; 
 scalar_t__ sequence_number ; 

__attribute__((used)) static void
sort_ids (struct head *head_ptr)
{
  /* id holds the current element to insert.  id_next holds the next
     element to insert.  id_ptr iterates through the already sorted elements
     looking for the place to insert id.  */
  struct id *id, *id_next, **id_ptr;

  id = head_ptr->first;

  /* We don't have any sorted elements yet.  */
  head_ptr->first = NULL;

  for (; id; id = id_next)
    {
      id_next = id->next;
      id->sequence = extract_init_priority (id->name);

      for (id_ptr = &(head_ptr->first); ; id_ptr = &((*id_ptr)->next))
	if (*id_ptr == NULL
	    /* If the sequence numbers are the same, we put the id from the
	       file later on the command line later in the list.  */
	    || id->sequence > (*id_ptr)->sequence
	    /* Hack: do lexical compare, too.
	    || (id->sequence == (*id_ptr)->sequence
		&& strcmp (id->name, (*id_ptr)->name) > 0) */
	    )
	  {
	    id->next = *id_ptr;
	    *id_ptr = id;
	    break;
	  }
    }

  /* Now set the sequence numbers properly so write_c_file works.  */
  for (id = head_ptr->first; id; id = id->next)
    id->sequence = ++sequence_number;
}