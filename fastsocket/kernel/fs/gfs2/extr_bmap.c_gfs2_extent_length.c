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
typedef  scalar_t__ u64 ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  const __be64 ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline unsigned int gfs2_extent_length(struct buffer_head *bh,
					      __be64 *ptr, unsigned limit,
					      int *eob)
{
	const __be64 *end = (const __be64 *)(bh->b_data + bh->b_size);
	const __be64 *first = ptr;
	u64 d = be64_to_cpu(*ptr);

	*eob = 0;
	do {
		ptr++;
		if (ptr >= end)
			break;
		if (limit && --limit == 0)
			break;
		if (d)
			d++;
	} while(be64_to_cpu(*ptr) == d);
	if (ptr >= end)
		*eob = 1;
	return (ptr - first);
}