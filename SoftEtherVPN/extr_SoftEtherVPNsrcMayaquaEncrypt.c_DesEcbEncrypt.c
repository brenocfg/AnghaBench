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
typedef  int /*<<< orphan*/  ks ;
typedef  int /*<<< orphan*/  key ;
typedef  int UCHAR ;
typedef  int* DES_key_schedule ;
typedef  int* DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ecb_encrypt (void*,void*,int**,int) ; 
 int /*<<< orphan*/  DES_set_key_unchecked (int**,int**) ; 
 int /*<<< orphan*/  DES_set_odd_parity (int**) ; 
 int /*<<< orphan*/  Zero (int**,int) ; 

void DesEcbEncrypt(void *dst, void *src, void *key_7bytes)
{
	UCHAR *key_56;
	DES_cblock key;
	DES_key_schedule ks;
	// Validate arguments
	if (dst == NULL || src == NULL || key_7bytes == NULL)
	{
		return;
	}

	key_56 = (UCHAR *)key_7bytes;

	Zero(&key, sizeof(key));
	Zero(&ks, sizeof(ks));

	key[0] = key_56[0];
	key[1] = (unsigned char)(((key_56[0] << 7) & 0xFF) | (key_56[1] >> 1));
	key[2] = (unsigned char)(((key_56[1] << 6) & 0xFF) | (key_56[2] >> 2));
	key[3] = (unsigned char)(((key_56[2] << 5) & 0xFF) | (key_56[3] >> 3));
	key[4] = (unsigned char)(((key_56[3] << 4) & 0xFF) | (key_56[4] >> 4));
	key[5] = (unsigned char)(((key_56[4] << 3) & 0xFF) | (key_56[5] >> 5));
	key[6] = (unsigned char)(((key_56[5] << 2) & 0xFF) | (key_56[6] >> 6));
	key[7] = (unsigned char) ((key_56[6] << 1) & 0xFF);

	DES_set_odd_parity(&key);
	DES_set_key_unchecked(&key, &ks);

	DES_ecb_encrypt(src, dst, &ks, 1);
}