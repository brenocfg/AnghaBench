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
 scalar_t__ MAX_CCLS_INCREMENT ; 
 int* ccl_has_nl ; 
 scalar_t__* ccllen ; 
 scalar_t__* cclmap ; 
 scalar_t__* cclng ; 
 scalar_t__ current_maxccls ; 
 scalar_t__ lastccl ; 
 int /*<<< orphan*/  num_reallocs ; 
 int* reallocate_bool_array (int*,scalar_t__) ; 
 scalar_t__* reallocate_integer_array (scalar_t__*,scalar_t__) ; 

int     cclinit ()
{
	if (++lastccl >= current_maxccls) {
		current_maxccls += MAX_CCLS_INCREMENT;

		++num_reallocs;

		cclmap =
			reallocate_integer_array (cclmap, current_maxccls);
		ccllen =
			reallocate_integer_array (ccllen, current_maxccls);
		cclng = reallocate_integer_array (cclng, current_maxccls);
		ccl_has_nl =
			reallocate_bool_array (ccl_has_nl,
					       current_maxccls);
	}

	if (lastccl == 1)
		/* we're making the first ccl */
		cclmap[lastccl] = 0;

	else
		/* The new pointer is just past the end of the last ccl.
		 * Since the cclmap points to the \first/ character of a
		 * ccl, adding the length of the ccl to the cclmap pointer
		 * will produce a cursor to the first free space.
		 */
		cclmap[lastccl] =
			cclmap[lastccl - 1] + ccllen[lastccl - 1];

	ccllen[lastccl] = 0;
	cclng[lastccl] = 0;	/* ccl's start out life un-negated */
	ccl_has_nl[lastccl] = false;

	return lastccl;
}