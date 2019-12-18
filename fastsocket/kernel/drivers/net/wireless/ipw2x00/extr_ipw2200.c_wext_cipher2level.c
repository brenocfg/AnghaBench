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
#define  IW_AUTH_CIPHER_CCMP 132 
#define  IW_AUTH_CIPHER_NONE 131 
#define  IW_AUTH_CIPHER_TKIP 130 
#define  IW_AUTH_CIPHER_WEP104 129 
#define  IW_AUTH_CIPHER_WEP40 128 
 int SEC_LEVEL_0 ; 
 int SEC_LEVEL_1 ; 
 int SEC_LEVEL_2 ; 
 int SEC_LEVEL_3 ; 

__attribute__((used)) static int wext_cipher2level(int cipher)
{
	switch (cipher) {
	case IW_AUTH_CIPHER_NONE:
		return SEC_LEVEL_0;
	case IW_AUTH_CIPHER_WEP40:
	case IW_AUTH_CIPHER_WEP104:
		return SEC_LEVEL_1;
	case IW_AUTH_CIPHER_TKIP:
		return SEC_LEVEL_2;
	case IW_AUTH_CIPHER_CCMP:
		return SEC_LEVEL_3;
	default:
		return -1;
	}
}