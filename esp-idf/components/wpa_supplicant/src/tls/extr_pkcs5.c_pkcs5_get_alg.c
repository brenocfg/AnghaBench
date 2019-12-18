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
struct asn1_oid {int len; int* oid; } ;
typedef  enum pkcs5_alg { ____Placeholder_pkcs5_alg } pkcs5_alg ;

/* Variables and functions */
 int PKCS5_ALG_MD5_DES_CBC ; 
 int PKCS5_ALG_UNKNOWN ; 

__attribute__((used)) static enum pkcs5_alg pkcs5_get_alg(struct asn1_oid *oid)
{
	if (oid->len == 7 &&
	    oid->oid[0] == 1 /* iso */ &&
	    oid->oid[1] == 2 /* member-body */ &&
	    oid->oid[2] == 840 /* us */ &&
	    oid->oid[3] == 113549 /* rsadsi */ &&
	    oid->oid[4] == 1 /* pkcs */ &&
	    oid->oid[5] == 5 /* pkcs-5 */ &&
	    oid->oid[6] == 3 /* pbeWithMD5AndDES-CBC */)
		return PKCS5_ALG_MD5_DES_CBC;

	return PKCS5_ALG_UNKNOWN;
}