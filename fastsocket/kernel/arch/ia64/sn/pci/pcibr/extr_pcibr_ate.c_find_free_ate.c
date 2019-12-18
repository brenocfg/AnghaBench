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
typedef  int /*<<< orphan*/  u64 ;
struct ate_resource {int num_ate; int /*<<< orphan*/ * ate; } ;

/* Variables and functions */

__attribute__((used)) static int find_free_ate(struct ate_resource *ate_resource, int start,
			 int count)
{
	u64 *ate = ate_resource->ate;
	int index;
	int start_free;

	for (index = start; index < ate_resource->num_ate;) {
		if (!ate[index]) {
			int i;
			int free;
			free = 0;
			start_free = index;	/* Found start free ate */
			for (i = start_free; i < ate_resource->num_ate; i++) {
				if (!ate[i]) {	/* This is free */
					if (++free == count)
						return start_free;
				} else {
					index = i + 1;
					break;
				}
			}
			if (i >= ate_resource->num_ate)
				return -1;
		} else
			index++;	/* Try next ate */
	}

	return -1;
}