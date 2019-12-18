#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fdtable {TYPE_1__* open_fds; } ;
typedef  int /*<<< orphan*/  fd_set_bits ;
struct TYPE_4__ {int /*<<< orphan*/  files; } ;
struct TYPE_3__ {unsigned long* fds_bits; } ;

/* Variables and functions */
 unsigned long BITS (int /*<<< orphan*/ *,unsigned long) ; 
 int EBADF ; 
 int __NFDBITS ; 
 TYPE_2__* current ; 
 struct fdtable* files_fdtable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max_select_fd(unsigned long n, fd_set_bits *fds)
{
	unsigned long *open_fds;
	unsigned long set;
	int max;
	struct fdtable *fdt;

	/* handle last in-complete long-word first */
	set = ~(~0UL << (n & (__NFDBITS-1)));
	n /= __NFDBITS;
	fdt = files_fdtable(current->files);
	open_fds = fdt->open_fds->fds_bits+n;
	max = 0;
	if (set) {
		set &= BITS(fds, n);
		if (set) {
			if (!(set & ~*open_fds))
				goto get_max;
			return -EBADF;
		}
	}
	while (n) {
		open_fds--;
		n--;
		set = BITS(fds, n);
		if (!set)
			continue;
		if (set & ~*open_fds)
			return -EBADF;
		if (max)
			continue;
get_max:
		do {
			max++;
			set >>= 1;
		} while (set);
		max += n * __NFDBITS;
	}

	return max;
}