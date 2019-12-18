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
struct hist_entry {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int repsep_snprintf (char*,size_t,char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_entry__cpu_snprintf(struct hist_entry *self, char *bf,
				       size_t size, unsigned int width)
{
	return repsep_snprintf(bf, size, "%-*d", width, self->cpu);
}