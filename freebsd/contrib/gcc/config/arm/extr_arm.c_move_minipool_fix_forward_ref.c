#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ max_address; scalar_t__ fix_size; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_1__ Mnode ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* minipool_vector_head ; 
 TYPE_1__* minipool_vector_tail ; 

__attribute__((used)) static Mnode *
move_minipool_fix_forward_ref (Mnode *mp, Mnode *max_mp,
			       HOST_WIDE_INT max_address)
{
  /* The code below assumes these are different.  */
  gcc_assert (mp != max_mp);

  if (max_mp == NULL)
    {
      if (max_address < mp->max_address)
	mp->max_address = max_address;
    }
  else
    {
      if (max_address > max_mp->max_address - mp->fix_size)
	mp->max_address = max_mp->max_address - mp->fix_size;
      else
	mp->max_address = max_address;

      /* Unlink MP from its current position.  Since max_mp is non-null,
       mp->prev must be non-null.  */
      mp->prev->next = mp->next;
      if (mp->next != NULL)
	mp->next->prev = mp->prev;
      else
	minipool_vector_tail = mp->prev;

      /* Re-insert it before MAX_MP.  */
      mp->next = max_mp;
      mp->prev = max_mp->prev;
      max_mp->prev = mp;

      if (mp->prev != NULL)
	mp->prev->next = mp;
      else
	minipool_vector_head = mp;
    }

  /* Save the new entry.  */
  max_mp = mp;

  /* Scan over the preceding entries and adjust their addresses as
     required.  */
  while (mp->prev != NULL
	 && mp->prev->max_address > mp->max_address - mp->prev->fix_size)
    {
      mp->prev->max_address = mp->max_address - mp->prev->fix_size;
      mp = mp->prev;
    }

  return max_mp;
}