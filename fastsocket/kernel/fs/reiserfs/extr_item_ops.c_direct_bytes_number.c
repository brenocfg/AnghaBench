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
struct item_head {int dummy; } ;

/* Variables and functions */
 int ih_item_len (struct item_head*) ; 

__attribute__((used)) static int direct_bytes_number(struct item_head *ih, int block_size)
{
	return ih_item_len(ih);
}