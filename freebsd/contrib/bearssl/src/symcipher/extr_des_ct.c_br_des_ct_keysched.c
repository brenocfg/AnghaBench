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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_des_rev_skey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keysched_unit (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

unsigned
br_des_ct_keysched(uint32_t *skey, const void *key, size_t key_len)
{
	switch (key_len) {
	case 8:
		keysched_unit(skey, key);
		return 1;
	case 16:
		keysched_unit(skey, key);
		keysched_unit(skey + 32, (const unsigned char *)key + 8);
		br_des_rev_skey(skey + 32);
		memcpy(skey + 64, skey, 32 * sizeof *skey);
		return 3;
	default:
		keysched_unit(skey, key);
		keysched_unit(skey + 32, (const unsigned char *)key + 8);
		br_des_rev_skey(skey + 32);
		keysched_unit(skey + 64, (const unsigned char *)key + 16);
		return 3;
	}
}