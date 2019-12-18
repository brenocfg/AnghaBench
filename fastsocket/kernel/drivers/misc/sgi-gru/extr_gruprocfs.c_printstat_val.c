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
typedef  int /*<<< orphan*/  atomic_long_t ;

/* Variables and functions */
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,char*) ; 

__attribute__((used)) static void printstat_val(struct seq_file *s, atomic_long_t *v, char *id)
{
	unsigned long val = atomic_long_read(v);

	seq_printf(s, "%16lu %s\n", val, id);
}