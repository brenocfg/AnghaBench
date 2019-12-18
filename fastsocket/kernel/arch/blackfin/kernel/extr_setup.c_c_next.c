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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* c_start (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  next_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	*pos = next_cpu(*pos, cpu_online_map);

	return c_start(m, pos);
}