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
union exp_element {struct block* block; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_exp_elt (union exp_element) ; 

void
write_exp_elt_block (struct block *b)
{
  union exp_element tmp;
  tmp.block = b;
  write_exp_elt (tmp);
}