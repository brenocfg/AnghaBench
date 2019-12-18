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
typedef  int etypes ;

/* Variables and functions */
#define  AES128_CTS_HMAC_SHA1_96 130 
#define  AES256_CTS_HMAC_SHA1_96 129 
#define  DES3_CBC_SHA1_KD 128 

__attribute__((used)) static const char *
etype_name(etypes etype)
{
	switch (etype) {
	case DES3_CBC_SHA1_KD:
		return ("des3-cbc-sha1");
	case AES128_CTS_HMAC_SHA1_96:
		return ("aes128-cts-hmac-sha1-96");
	case AES256_CTS_HMAC_SHA1_96:
		return ("aes-cts-hmac-sha1-96");
	default:
		return ("unknown enctype");
	}
}