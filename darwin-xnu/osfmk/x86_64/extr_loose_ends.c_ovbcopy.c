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
typedef  int vm_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy_no_overwrite (char const*,char*,int) ; 

void
ovbcopy(
	const char	*from,
	char		*to,
	vm_size_t	bytes)		/* num bytes to copy */
{
	/* Assume that bcopy copies left-to-right (low addr first). */
	if (from + bytes <= to || to + bytes <= from || to == from)
		bcopy_no_overwrite(from, to, bytes);	/* non-overlapping or no-op*/
	else if (from > to)
		bcopy_no_overwrite(from, to, bytes);	/* overlapping but OK */
	else {
		/* to > from: overlapping, and must copy right-to-left. */
		from += bytes - 1;
		to += bytes - 1;
		while (bytes-- > 0)
			*to-- = *from--;
	}
}