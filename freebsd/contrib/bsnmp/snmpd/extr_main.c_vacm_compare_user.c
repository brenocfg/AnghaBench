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
typedef  size_t uint32_t ;
struct vacm_user {scalar_t__ sec_model; scalar_t__* secname; } ;

/* Variables and functions */
 size_t strlen (scalar_t__*) ; 

__attribute__((used)) static int
vacm_compare_user(struct vacm_user *v1, struct vacm_user *v2)
{
	uint32_t i;

	if (v1->sec_model < v2->sec_model)
		return (-1);
	if (v1->sec_model > v2->sec_model)
		return (1);

	if (strlen(v1->secname) < strlen(v2->secname))
		return (-1);
	if (strlen(v1->secname) > strlen(v2->secname))
		return (1);

	for (i = 0; i < strlen(v1->secname); i++) {
		if (v1->secname[i] < v2->secname[i])
			return (-1);
		if (v1->secname[i] > v2->secname[i])
			return (1);
	}

	return (0);
}