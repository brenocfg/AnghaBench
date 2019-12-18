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
#define  BR_EC_secp256r1 130 
#define  BR_EC_secp384r1 129 
#define  BR_EC_secp521r1 128 

const unsigned char *
br_get_curve_OID(int curve)
{
	static const unsigned char OID_secp256r1[] = {
		0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07
	};
	static const unsigned char OID_secp384r1[] = {
		0x05, 0x2b, 0x81, 0x04, 0x00, 0x22
	};
	static const unsigned char OID_secp521r1[] = {
		0x05, 0x2b, 0x81, 0x04, 0x00, 0x23
	};

	switch (curve) {
	case BR_EC_secp256r1:  return OID_secp256r1;
	case BR_EC_secp384r1:  return OID_secp384r1;
	case BR_EC_secp521r1:  return OID_secp521r1;
	default:
		return NULL;
	}
}