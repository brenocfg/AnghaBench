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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int BIGGEST_ALIGNMENT ; 
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int exact_log2 (int) ; 

__attribute__((used)) static int
final_addr_vec_align (rtx addr_vec)
{
  int align = GET_MODE_SIZE (GET_MODE (PATTERN (addr_vec)));

  if (align > BIGGEST_ALIGNMENT / BITS_PER_UNIT)
    align = BIGGEST_ALIGNMENT / BITS_PER_UNIT;
  return exact_log2 (align);

}