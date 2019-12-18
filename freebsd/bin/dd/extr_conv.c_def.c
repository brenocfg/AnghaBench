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
typedef  size_t u_char ;
struct TYPE_4__ {size_t* dbp; size_t dbrcnt; scalar_t__ dbcnt; } ;
struct TYPE_3__ {size_t* dbp; scalar_t__ dbcnt; scalar_t__ dbsz; } ;

/* Variables and functions */
 size_t* ctab ; 
 int /*<<< orphan*/  dd_out (int /*<<< orphan*/ ) ; 
 TYPE_2__ in ; 
 TYPE_1__ out ; 

void
def(void)
{
	u_char *inp;
	const u_char *t;
	size_t cnt;

	if ((t = ctab) != NULL)
		for (inp = in.dbp - (cnt = in.dbrcnt); cnt--; ++inp)
			*inp = t[*inp];

	/* Make the output buffer look right. */
	out.dbp = in.dbp;
	out.dbcnt = in.dbcnt;

	if (in.dbcnt >= out.dbsz) {
		/* If the output buffer is full, write it. */
		dd_out(0);

		/*
		 * dd_out copies the leftover output to the beginning of
		 * the buffer and resets the output buffer.  Reset the
		 * input buffer to match it.
	 	 */
		in.dbp = out.dbp;
		in.dbcnt = out.dbcnt;
	}
}