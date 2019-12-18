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
struct TYPE_3__ {int /*<<< orphan*/  nr_frees; scalar_t__ cmd_pool_bits; int /*<<< orphan*/ * cmd_pool; } ;
typedef  TYPE_1__ ctlr_info_t ;
typedef  int /*<<< orphan*/  CommandList_struct ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  clear_bit (int,scalar_t__) ; 

__attribute__((used)) static void cmd_free(ctlr_info_t *h, CommandList_struct *c)
{
	int i;

	i = c - h->cmd_pool;
	clear_bit(i & (BITS_PER_LONG - 1),
		  h->cmd_pool_bits + (i / BITS_PER_LONG));
	h->nr_frees++;
}