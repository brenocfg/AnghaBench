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
struct uwb_rc {int beaconing; int /*<<< orphan*/  ies_mutex; int /*<<< orphan*/  ies; } ;
struct uwb_ie_hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uwb_ie_hdr* uwb_ie_next (void**,size_t*) ; 
 int uwb_rc_ie_add_one (struct uwb_rc*,struct uwb_ie_hdr const*) ; 
 int uwb_rc_set_ie (struct uwb_rc*,int /*<<< orphan*/ ) ; 

int uwb_rc_ie_add(struct uwb_rc *uwb_rc,
		  const struct uwb_ie_hdr *ies, size_t size)
{
	int result = 0;
	void *ptr;
	const struct uwb_ie_hdr *ie;

	mutex_lock(&uwb_rc->ies_mutex);

	ptr = (void *)ies;
	for (;;) {
		ie = uwb_ie_next(&ptr, &size);
		if (!ie)
			break;

		result = uwb_rc_ie_add_one(uwb_rc, ie);
		if (result < 0)
			break;
	}
	if (result >= 0) {
		if (size == 0) {
			if (uwb_rc->beaconing != -1)
				result = uwb_rc_set_ie(uwb_rc, uwb_rc->ies);
		} else
			result = -EINVAL;
	}

	mutex_unlock(&uwb_rc->ies_mutex);

	return result;
}