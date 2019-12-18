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
 unsigned char const** HASH_OID ; 

const unsigned char *
get_hash_oid(int id)
{
	if (id >= 2 && id <= 6) {
		return HASH_OID[id - 2];
	} else {
		return NULL;
	}
}