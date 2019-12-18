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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* record_layout_info ;
struct TYPE_3__ {int /*<<< orphan*/  bitpos; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_from_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
rli_size_so_far (record_layout_info rli)
{
  return bit_from_pos (rli->offset, rli->bitpos);
}