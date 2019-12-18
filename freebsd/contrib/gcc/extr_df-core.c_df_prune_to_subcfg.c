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
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned
df_prune_to_subcfg (int list[], unsigned len, bitmap blocks)
{
  unsigned act, last;

  for (act = 0, last = 0; act < len; act++)
    if (bitmap_bit_p (blocks, list[act]))
      list[last++] = list[act];

  return last;
}