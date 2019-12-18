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
#define  BR_EC_brainpoolP256r1 155 
#define  BR_EC_brainpoolP384r1 154 
#define  BR_EC_brainpoolP512r1 153 
#define  BR_EC_secp160k1 152 
#define  BR_EC_secp160r1 151 
#define  BR_EC_secp160r2 150 
#define  BR_EC_secp192k1 149 
#define  BR_EC_secp192r1 148 
#define  BR_EC_secp224k1 147 
#define  BR_EC_secp224r1 146 
#define  BR_EC_secp256k1 145 
#define  BR_EC_secp256r1 144 
#define  BR_EC_secp384r1 143 
#define  BR_EC_secp521r1 142 
#define  BR_EC_sect163k1 141 
#define  BR_EC_sect163r1 140 
#define  BR_EC_sect163r2 139 
#define  BR_EC_sect193r1 138 
#define  BR_EC_sect193r2 137 
#define  BR_EC_sect233k1 136 
#define  BR_EC_sect233r1 135 
#define  BR_EC_sect239k1 134 
#define  BR_EC_sect283k1 133 
#define  BR_EC_sect283r1 132 
#define  BR_EC_sect409k1 131 
#define  BR_EC_sect409r1 130 
#define  BR_EC_sect571k1 129 
#define  BR_EC_sect571r1 128 

__attribute__((used)) static const char *
curve_to_sym(int curve)
{
	switch (curve) {
	case BR_EC_sect163k1:         return "BR_EC_sect163k1";
	case BR_EC_sect163r1:         return "BR_EC_sect163r1";
	case BR_EC_sect163r2:         return "BR_EC_sect163r2";
	case BR_EC_sect193r1:         return "BR_EC_sect193r1";
	case BR_EC_sect193r2:         return "BR_EC_sect193r2";
	case BR_EC_sect233k1:         return "BR_EC_sect233k1";
	case BR_EC_sect233r1:         return "BR_EC_sect233r1";
	case BR_EC_sect239k1:         return "BR_EC_sect239k1";
	case BR_EC_sect283k1:         return "BR_EC_sect283k1";
	case BR_EC_sect283r1:         return "BR_EC_sect283r1";
	case BR_EC_sect409k1:         return "BR_EC_sect409k1";
	case BR_EC_sect409r1:         return "BR_EC_sect409r1";
	case BR_EC_sect571k1:         return "BR_EC_sect571k1";
	case BR_EC_sect571r1:         return "BR_EC_sect571r1";
	case BR_EC_secp160k1:         return "BR_EC_secp160k1";
	case BR_EC_secp160r1:         return "BR_EC_secp160r1";
	case BR_EC_secp160r2:         return "BR_EC_secp160r2";
	case BR_EC_secp192k1:         return "BR_EC_secp192k1";
	case BR_EC_secp192r1:         return "BR_EC_secp192r1";
	case BR_EC_secp224k1:         return "BR_EC_secp224k1";
	case BR_EC_secp224r1:         return "BR_EC_secp224r1";
	case BR_EC_secp256k1:         return "BR_EC_secp256k1";
	case BR_EC_secp256r1:         return "BR_EC_secp256r1";
	case BR_EC_secp384r1:         return "BR_EC_secp384r1";
	case BR_EC_secp521r1:         return "BR_EC_secp521r1";
	case BR_EC_brainpoolP256r1:   return "BR_EC_brainpoolP256r1";
	case BR_EC_brainpoolP384r1:   return "BR_EC_brainpoolP384r1";
	case BR_EC_brainpoolP512r1:   return "BR_EC_brainpoolP512r1";
	}
	return NULL;
}