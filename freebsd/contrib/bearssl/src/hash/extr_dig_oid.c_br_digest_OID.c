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
#define  br_md5_ID 133 
#define  br_sha1_ID 132 
#define  br_sha224_ID 131 
#define  br_sha256_ID 130 
#define  br_sha384_ID 129 
#define  br_sha512_ID 128 
 unsigned char const* md5_OID ; 
 unsigned char const* sha1_OID ; 
 unsigned char const* sha224_OID ; 
 unsigned char const* sha256_OID ; 
 unsigned char const* sha384_OID ; 
 unsigned char const* sha512_OID ; 

const unsigned char *
br_digest_OID(int digest_id, size_t *len)
{
	switch (digest_id) {
	case br_md5_ID:
		*len = sizeof md5_OID;
		return md5_OID;
	case br_sha1_ID:
		*len = sizeof sha1_OID;
		return sha1_OID;
	case br_sha224_ID:
		*len = sizeof sha224_OID;
		return sha224_OID;
	case br_sha256_ID:
		*len = sizeof sha256_OID;
		return sha256_OID;
	case br_sha384_ID:
		*len = sizeof sha384_OID;
		return sha384_OID;
	case br_sha512_ID:
		*len = sizeof sha512_OID;
		return sha512_OID;
	default:
		*len = 0;
		return NULL;
	}
}