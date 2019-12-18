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
struct segment {int nsec; struct section** v_sec; } ;
struct section {scalar_t__ off; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 struct section** realloc (struct section**,int) ; 

__attribute__((used)) static void
insert_to_inseg_list(struct segment *seg, struct section *sec)
{
	struct section *s;
	int i;

	seg->nsec++;
	seg->v_sec = realloc(seg->v_sec, seg->nsec * sizeof(*seg->v_sec));
	if (seg->v_sec == NULL)
		err(EXIT_FAILURE, "realloc failed");

	/*
	 * Sort the section in order of offset.
	 */

	for (i = seg->nsec - 1; i > 0; i--) {
		s = seg->v_sec[i - 1];
		if (sec->off >= s->off) {
			seg->v_sec[i] = sec;
			break;
		} else
			seg->v_sec[i] = s;
	}
	if (i == 0)
		seg->v_sec[0] = sec;
}