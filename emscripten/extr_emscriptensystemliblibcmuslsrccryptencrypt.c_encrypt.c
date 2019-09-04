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
struct expanded_key {int /*<<< orphan*/ * r; int /*<<< orphan*/ * l; } ;

/* Variables and functions */
 int /*<<< orphan*/  __do_des (int,int,int*,int*,int,int /*<<< orphan*/ ,struct expanded_key*) ; 
 struct expanded_key __encrypt_key ; 

void encrypt(char *block, int edflag)
{
	struct expanded_key decrypt_key, *key;
	uint32_t b[2];
	int i, j;
	char *p;

	p = block;
	for (i = 0; i < 2; i++) {
		b[i] = 0;
		for (j = 31; j >= 0; j--, p++)
			b[i] |= (uint32_t)(*p & 1) << j;
	}

	key = &__encrypt_key;
	if (edflag) {
		key = &decrypt_key;
		for (i = 0; i < 16; i++) {
			decrypt_key.l[i] = __encrypt_key.l[15-i];
			decrypt_key.r[i] = __encrypt_key.r[15-i];
		}
	}

	__do_des(b[0], b[1], b, b + 1, 1, 0, key);

	p = block;
	for (i = 0; i < 2; i++)
		for (j = 31; j >= 0; j--)
			*p++ = b[i]>>j & 1;
}