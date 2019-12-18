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
typedef  TYPE_1__* record_layout_info ;
struct TYPE_5__ {scalar_t__ (* ms_bitfield_layout_p ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int record_align; int unpacked_align; int offset_align; int remaining_in_alignment; scalar_t__ pending_statics; scalar_t__ packed_maybe_necessary; int /*<<< orphan*/  t; int /*<<< orphan*/  bitpos; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_tree (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_node_brief (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

void
debug_rli (record_layout_info rli)
{
  print_node_brief (stderr, "type", rli->t, 0);
  print_node_brief (stderr, "\noffset", rli->offset, 0);
  print_node_brief (stderr, " bitpos", rli->bitpos, 0);

  fprintf (stderr, "\naligns: rec = %u, unpack = %u, off = %u\n",
	   rli->record_align, rli->unpacked_align,
	   rli->offset_align);

  /* The ms_struct code is the only that uses this.  */
  if (targetm.ms_bitfield_layout_p (rli->t))
    fprintf (stderr, "remaining in alignment = %u\n", rli->remaining_in_alignment);

  if (rli->packed_maybe_necessary)
    fprintf (stderr, "packed may be necessary\n");

  if (rli->pending_statics)
    {
      fprintf (stderr, "pending statics:\n");
      debug_tree (rli->pending_statics);
    }
}