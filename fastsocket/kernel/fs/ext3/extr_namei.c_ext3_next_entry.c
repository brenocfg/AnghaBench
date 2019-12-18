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
struct ext3_dir_entry_2 {int /*<<< orphan*/  rec_len; } ;

/* Variables and functions */
 int ext3_rec_len_from_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ext3_dir_entry_2 *
ext3_next_entry(struct ext3_dir_entry_2 *p)
{
	return (struct ext3_dir_entry_2 *)((char *)p +
		ext3_rec_len_from_disk(p->rec_len));
}