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
struct dso {size_t relro_start; size_t relro_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (size_t*) ; 
 size_t* laddr (struct dso*,size_t) ; 

__attribute__((used)) static void reclaim(struct dso *dso, size_t start, size_t end)
{
	size_t *a, *z;
	if (start >= dso->relro_start && start < dso->relro_end) start = dso->relro_end;
	if (end   >= dso->relro_start && end   < dso->relro_end) end = dso->relro_start;
	start = start + 6*sizeof(size_t)-1 & -4*sizeof(size_t);
	end = (end & -4*sizeof(size_t)) - 2*sizeof(size_t);
	if (start>end || end-start < 4*sizeof(size_t)) return;
	a = laddr(dso, start);
	z = laddr(dso, end);
	a[-2] = 1;
	a[-1] = z[0] = end-start + 2*sizeof(size_t) | 1;
	z[1] = 1;
	free(a);
}