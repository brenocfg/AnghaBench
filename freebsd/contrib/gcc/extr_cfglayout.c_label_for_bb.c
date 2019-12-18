#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_HEAD (TYPE_1__*) ; 
 int /*<<< orphan*/  LABEL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_label (TYPE_1__*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 

__attribute__((used)) static rtx
label_for_bb (basic_block bb)
{
  rtx label = BB_HEAD (bb);

  if (!LABEL_P (label))
    {
      if (dump_file)
	fprintf (dump_file, "Emitting label for block %d\n", bb->index);

      label = block_label (bb);
    }

  return label;
}