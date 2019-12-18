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
struct kallsym_iter {char* name; int /*<<< orphan*/  pos; int /*<<< orphan*/  nameoff; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_symbol_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_iter(struct kallsym_iter *iter, loff_t new_pos)
{
	iter->name[0] = '\0';
	iter->nameoff = get_symbol_offset(new_pos);
	iter->pos = new_pos;
}