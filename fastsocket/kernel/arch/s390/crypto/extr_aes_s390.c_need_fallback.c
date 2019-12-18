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
 int AES_KEYLEN_128 ; 
 int AES_KEYLEN_192 ; 
 int AES_KEYLEN_256 ; 
 int keylen_flag ; 

__attribute__((used)) static int need_fallback(unsigned int key_len)
{
	switch (key_len) {
	case 16:
		if (!(keylen_flag & AES_KEYLEN_128))
			return 1;
		break;
	case 24:
		if (!(keylen_flag & AES_KEYLEN_192))
			return 1;
		break;
	case 32:
		if (!(keylen_flag & AES_KEYLEN_256))
			return 1;
		break;
	default:
		return -1;
		break;
	}
	return 0;
}