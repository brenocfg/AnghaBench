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
struct slabinfo {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct slabinfo*,struct slabinfo*,int) ; 
 scalar_t__ show_inverted ; 
 scalar_t__ slab_activity (struct slabinfo*) ; 
 scalar_t__ slab_size (struct slabinfo*) ; 
 struct slabinfo* slabinfo ; 
 int slabs ; 
 scalar_t__ sort_active ; 
 scalar_t__ sort_size ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sort_slabs(void)
{
	struct slabinfo *s1,*s2;

	for (s1 = slabinfo; s1 < slabinfo + slabs; s1++) {
		for (s2 = s1 + 1; s2 < slabinfo + slabs; s2++) {
			int result;

			if (sort_size)
				result = slab_size(s1) < slab_size(s2);
			else if (sort_active)
				result = slab_activity(s1) < slab_activity(s2);
			else
				result = strcasecmp(s1->name, s2->name);

			if (show_inverted)
				result = -result;

			if (result > 0) {
				struct slabinfo t;

				memcpy(&t, s1, sizeof(struct slabinfo));
				memcpy(s1, s2, sizeof(struct slabinfo));
				memcpy(s2, &t, sizeof(struct slabinfo));
			}
		}
	}
}