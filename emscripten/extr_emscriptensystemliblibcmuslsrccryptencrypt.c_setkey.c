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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __des_setkey (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __encrypt_key ; 

void setkey(const char *key)
{
	unsigned char bkey[8];
	int i, j;

	for (i = 0; i < 8; i++) {
		bkey[i] = 0;
		for (j = 7; j >= 0; j--, key++)
			bkey[i] |= (uint32_t)(*key & 1) << j;
	}

	__des_setkey(bkey, &__encrypt_key);
}