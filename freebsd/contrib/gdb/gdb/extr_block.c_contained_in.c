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
struct block {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLOCK_END (struct block const*) ; 
 scalar_t__ BLOCK_START (struct block const*) ; 

int
contained_in (const struct block *a, const struct block *b)
{
  if (!a || !b)
    return 0;
  return BLOCK_START (a) >= BLOCK_START (b)
    && BLOCK_END (a) <= BLOCK_END (b);
}