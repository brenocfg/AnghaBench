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

/* Variables and functions */
 scalar_t__ _stext ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 size_t min (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/ * prof_buffer ; 
 scalar_t__ prof_len ; 
 int prof_on ; 
 unsigned long prof_shift ; 

void profile_hits(int type, void *__pc, unsigned int nr_hits)
{
	unsigned long pc;

	if (prof_on != type || !prof_buffer)
		return;
	pc = ((unsigned long)__pc - (unsigned long)_stext) >> prof_shift;
	atomic_add(nr_hits, &prof_buffer[min(pc, prof_len - 1)]);
}