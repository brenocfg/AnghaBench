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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_BIT_STRING_new () ; 
 int /*<<< orphan*/  BitStringSetBit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NID_key_usage ; 
 int /*<<< orphan*/ * X509V3_EXT_i2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

X509_EXTENSION *NewBasicKeyUsageForX509()
{
	X509_EXTENSION *ret = NULL;
	ASN1_BIT_STRING *str;

	str = ASN1_BIT_STRING_new();
	if (str != NULL)
	{
		BitStringSetBit(str, 0);	// KU_DIGITAL_SIGNATURE
		BitStringSetBit(str, 1);	// KU_NON_REPUDIATION
		BitStringSetBit(str, 2);	// KU_KEY_ENCIPHERMENT
		BitStringSetBit(str, 3);	// KU_DATA_ENCIPHERMENT
		//BitStringSetBit(str, 4);	// KU_KEY_AGREEMENT
		BitStringSetBit(str, 5);	// KU_KEY_CERT_SIGN
		BitStringSetBit(str, 6);	// KU_CRL_SIGN

		ret = X509V3_EXT_i2d(NID_key_usage, 0, str);

		ASN1_BIT_STRING_free(str);
	}

	return ret;
}