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
struct exofs_dir_entry {scalar_t__ rec_len; } ;

/* Variables and functions */
 struct exofs_dir_entry* exofs_next_entry (struct exofs_dir_entry*) ; 

__attribute__((used)) static inline unsigned
exofs_validate_entry(char *base, unsigned offset, unsigned mask)
{
	struct exofs_dir_entry *de = (struct exofs_dir_entry *)(base + offset);
	struct exofs_dir_entry *p =
			(struct exofs_dir_entry *)(base + (offset&mask));
	while ((char *)p < (char *)de) {
		if (p->rec_len == 0)
			break;
		p = exofs_next_entry(p);
	}
	return (char *)p - base;
}