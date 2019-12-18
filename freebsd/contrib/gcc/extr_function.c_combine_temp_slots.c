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
struct temp_slot {scalar_t__ base_offset; scalar_t__ full_size; scalar_t__ size; int /*<<< orphan*/  slot; struct temp_slot* next; } ;

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 struct temp_slot* avail_temp_slots ; 
 int /*<<< orphan*/  cut_slot_from_list (struct temp_slot*,struct temp_slot**) ; 
 int /*<<< orphan*/  flag_expensive_optimizations ; 
 scalar_t__ flag_strict_aliasing ; 
 scalar_t__ optimize ; 

__attribute__((used)) static void
combine_temp_slots (void)
{
  struct temp_slot *p, *q, *next, *next_q;
  int num_slots;

  /* We can't combine slots, because the information about which slot
     is in which alias set will be lost.  */
  if (flag_strict_aliasing)
    return;

  /* If there are a lot of temp slots, don't do anything unless
     high levels of optimization.  */
  if (! flag_expensive_optimizations)
    for (p = avail_temp_slots, num_slots = 0; p; p = p->next, num_slots++)
      if (num_slots > 100 || (num_slots > 10 && optimize == 0))
	return;

  for (p = avail_temp_slots; p; p = next)
    {
      int delete_p = 0;

      next = p->next;

      if (GET_MODE (p->slot) != BLKmode)
	continue;

      for (q = p->next; q; q = next_q)
	{
       	  int delete_q = 0;

	  next_q = q->next;

	  if (GET_MODE (q->slot) != BLKmode)
	    continue;

	  if (p->base_offset + p->full_size == q->base_offset)
	    {
	      /* Q comes after P; combine Q into P.  */
	      p->size += q->size;
	      p->full_size += q->full_size;
	      delete_q = 1;
	    }
	  else if (q->base_offset + q->full_size == p->base_offset)
	    {
	      /* P comes after Q; combine P into Q.  */
	      q->size += p->size;
	      q->full_size += p->full_size;
	      delete_p = 1;
	      break;
	    }
	  if (delete_q)
	    cut_slot_from_list (q, &avail_temp_slots);
	}

      /* Either delete P or advance past it.  */
      if (delete_p)
	cut_slot_from_list (p, &avail_temp_slots);
    }
}