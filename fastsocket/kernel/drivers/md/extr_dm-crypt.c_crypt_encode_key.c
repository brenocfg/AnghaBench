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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void crypt_encode_key(char *hex, u8 *key, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++) {
		sprintf(hex, "%02x", *key);
		hex += 2;
		key++;
	}
}