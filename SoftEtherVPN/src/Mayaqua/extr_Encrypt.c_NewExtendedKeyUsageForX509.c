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
typedef  int /*<<< orphan*/  EXTENDED_KEY_USAGE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free ; 
 int /*<<< orphan*/  AddKeyUsageX509 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_OCSP_sign ; 
 int /*<<< orphan*/  NID_client_auth ; 
 int /*<<< orphan*/  NID_code_sign ; 
 int /*<<< orphan*/  NID_email_protect ; 
 int /*<<< orphan*/  NID_ext_key_usage ; 
 int /*<<< orphan*/  NID_ipsecEndSystem ; 
 int /*<<< orphan*/  NID_ipsecTunnel ; 
 int /*<<< orphan*/  NID_ipsecUser ; 
 int /*<<< orphan*/  NID_server_auth ; 
 int /*<<< orphan*/  NID_time_stamp ; 
 int /*<<< orphan*/ * X509V3_EXT_i2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ASN1_OBJECT_new_null () ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

X509_EXTENSION *NewExtendedKeyUsageForX509()
{
	EXTENDED_KEY_USAGE *ex = sk_ASN1_OBJECT_new_null();
	X509_EXTENSION *ret;

	AddKeyUsageX509(ex, NID_server_auth);
	AddKeyUsageX509(ex, NID_client_auth);
	AddKeyUsageX509(ex, NID_code_sign);
	AddKeyUsageX509(ex, NID_email_protect);
	AddKeyUsageX509(ex, NID_ipsecEndSystem);
	AddKeyUsageX509(ex, NID_ipsecTunnel);
	AddKeyUsageX509(ex, NID_ipsecUser);
	AddKeyUsageX509(ex, NID_time_stamp);
	AddKeyUsageX509(ex, NID_OCSP_sign);

	ret = X509V3_EXT_i2d(NID_ext_key_usage, 0, ex);

	sk_ASN1_OBJECT_pop_free(ex, ASN1_OBJECT_free);

	return ret;
}