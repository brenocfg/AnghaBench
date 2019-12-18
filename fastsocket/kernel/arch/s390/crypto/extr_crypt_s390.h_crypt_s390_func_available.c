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
 int CRYPT_S390_FUNC_MASK ; 
#define  CRYPT_S390_KIMD 133 
#define  CRYPT_S390_KLMD 132 
#define  CRYPT_S390_KM 131 
#define  CRYPT_S390_KMAC 130 
#define  CRYPT_S390_KMC 129 
#define  CRYPT_S390_KMCTR 128 
 unsigned int CRYPT_S390_MSA ; 
 unsigned int CRYPT_S390_MSA3 ; 
 unsigned int CRYPT_S390_MSA4 ; 
 int CRYPT_S390_OP_MASK ; 
 int /*<<< orphan*/  KIMD_QUERY ; 
 int /*<<< orphan*/  KLMD_QUERY ; 
 int /*<<< orphan*/  KMAC_QUERY ; 
 int /*<<< orphan*/  KMCTR_QUERY ; 
 int /*<<< orphan*/  KMC_QUERY ; 
 int /*<<< orphan*/  KM_QUERY ; 
 int crypt_s390_kimd (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypt_s390_klmd (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypt_s390_km (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypt_s390_kmac (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypt_s390_kmc (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypt_s390_kmctr (int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long long stfl () ; 
 scalar_t__ stfle (unsigned long long*,int) ; 

__attribute__((used)) static inline int crypt_s390_func_available(int func,
					unsigned int facility_mask)
{
	unsigned long long facility_bits[2];
	unsigned char status[16];
	int ret;

	if (facility_mask & CRYPT_S390_MSA &&
	    !(stfl() & 1ULL << (31 - 17)))
		return 0;

	if (facility_mask & CRYPT_S390_MSA3 ||
	    facility_mask & CRYPT_S390_MSA4)
		if (stfle(facility_bits, 2) <= 0)
			return 0;

	if (facility_mask & CRYPT_S390_MSA3 &&
	    !(facility_bits[1] & (1ULL << (63 - (76 - 64)))))
		return 0;
	if (facility_mask & CRYPT_S390_MSA4 &&
	    !(facility_bits[1] & (1ULL << (63 - (77 - 64)))))
		return 0;

	switch (func & CRYPT_S390_OP_MASK) {
	case CRYPT_S390_KM:
		ret = crypt_s390_km(KM_QUERY, &status, NULL, NULL, 0);
		break;
	case CRYPT_S390_KMC:
		ret = crypt_s390_kmc(KMC_QUERY, &status, NULL, NULL, 0);
		break;
	case CRYPT_S390_KIMD:
		ret = crypt_s390_kimd(KIMD_QUERY, &status, NULL, 0);
		break;
	case CRYPT_S390_KLMD:
		ret = crypt_s390_klmd(KLMD_QUERY, &status, NULL, 0);
		break;
	case CRYPT_S390_KMAC:
		ret = crypt_s390_kmac(KMAC_QUERY, &status, NULL, 0);
		break;
	case CRYPT_S390_KMCTR:
		ret = crypt_s390_kmctr(KMCTR_QUERY, &status, NULL, NULL, 0,
				       NULL);
		break;
	default:
		return 0;
	}
	if (ret < 0)
		return 0;
	func &= CRYPT_S390_FUNC_MASK;
	func &= 0x7f;		/* mask modifier bit */
	return (status[func >> 3] & (0x80 >> (func & 7))) != 0;
}