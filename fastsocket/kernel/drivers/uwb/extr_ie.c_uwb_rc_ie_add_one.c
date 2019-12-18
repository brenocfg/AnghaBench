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
struct uwb_rc_cmd_set_ie {int /*<<< orphan*/  wIELength; void* IEData; } ;
struct uwb_rc {size_t ies_capacity; struct uwb_rc_cmd_set_ie* ies; } ;
struct uwb_ie_hdr {int length; scalar_t__ element_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 struct uwb_rc_cmd_set_ie* krealloc (struct uwb_rc_cmd_set_ie*,size_t,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,struct uwb_ie_hdr const*,size_t) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 
 struct uwb_ie_hdr* uwb_ie_next (void**,size_t*) ; 

__attribute__((used)) static int uwb_rc_ie_add_one(struct uwb_rc *rc, const struct uwb_ie_hdr *new_ie)
{
	struct uwb_rc_cmd_set_ie *new_ies;
	void *ptr, *prev_ie;
	struct uwb_ie_hdr *ie;
	size_t length, new_ie_len, new_capacity, size, prev_size;

	length = le16_to_cpu(rc->ies->wIELength);
	new_ie_len = sizeof(struct uwb_ie_hdr) + new_ie->length;
	new_capacity = sizeof(struct uwb_rc_cmd_set_ie) + length + new_ie_len;

	if (new_capacity > rc->ies_capacity) {
		new_ies = krealloc(rc->ies, new_capacity, GFP_KERNEL);
		if (!new_ies)
			return -ENOMEM;
		rc->ies = new_ies;
	}

	ptr = rc->ies->IEData;
	size = length;
	for (;;) {
		prev_ie = ptr;
		prev_size = size;
		ie = uwb_ie_next(&ptr, &size);
		if (!ie || ie->element_id > new_ie->element_id)
			break;
	}

	memmove(prev_ie + new_ie_len, prev_ie, prev_size);
	memcpy(prev_ie, new_ie, new_ie_len);
	rc->ies->wIELength = cpu_to_le16(length + new_ie_len);

	return 0;
}