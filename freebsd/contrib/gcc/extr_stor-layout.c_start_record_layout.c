#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct record_layout_info_s {int dummy; } ;
typedef  TYPE_1__* record_layout_info ;
struct TYPE_4__ {scalar_t__ remaining_in_alignment; scalar_t__ packed_maybe_necessary; scalar_t__ pending_statics; scalar_t__ prev_field; int /*<<< orphan*/  bitpos; int /*<<< orphan*/  offset; void* record_align; void* offset_align; void* unpacked_align; int /*<<< orphan*/  t; } ;

/* Variables and functions */
 unsigned int BIGGEST_ALIGNMENT ; 
 void* BITS_PER_UNIT ; 
 void* MAX (void*,unsigned int) ; 
 scalar_t__ STRUCTURE_SIZE_BOUNDARY ; 
 unsigned int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PACKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitsize_zero_node ; 
 int /*<<< orphan*/  size_zero_node ; 
 TYPE_1__* xmalloc (int) ; 

record_layout_info
start_record_layout (tree t)
{
  record_layout_info rli = xmalloc (sizeof (struct record_layout_info_s));

  rli->t = t;

  /* If the type has a minimum specified alignment (via an attribute
     declaration, for example) use it -- otherwise, start with a
     one-byte alignment.  */
  rli->record_align = MAX (BITS_PER_UNIT, TYPE_ALIGN (t));
  rli->unpacked_align = rli->record_align;
  rli->offset_align = MAX (rli->record_align, BIGGEST_ALIGNMENT);

#ifdef STRUCTURE_SIZE_BOUNDARY
  /* Packed structures don't need to have minimum size.  */
  if (! TYPE_PACKED (t))
    rli->record_align = MAX (rli->record_align, (unsigned) STRUCTURE_SIZE_BOUNDARY);
#endif

  rli->offset = size_zero_node;
  rli->bitpos = bitsize_zero_node;
  rli->prev_field = 0;
  rli->pending_statics = 0;
  rli->packed_maybe_necessary = 0;
  rli->remaining_in_alignment = 0;

  return rli;
}