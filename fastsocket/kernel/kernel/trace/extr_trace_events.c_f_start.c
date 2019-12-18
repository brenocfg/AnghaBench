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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ FORMAT_HEADER ; 
 void* f_next (struct seq_file*,void*,scalar_t__*) ; 

__attribute__((used)) static void *f_start(struct seq_file *m, loff_t *pos)
{
	loff_t l = 0;
	void *p;

	/* Start by showing the header */
	if (!*pos)
		return (void *)FORMAT_HEADER;

	p = (void *)FORMAT_HEADER;
	do {
		p = f_next(m, p, &l);
	} while (p && l < *pos);

	return p;
}