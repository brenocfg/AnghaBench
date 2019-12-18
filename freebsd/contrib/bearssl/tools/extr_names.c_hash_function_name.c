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
#define  br_md5_ID 134 
#define  br_md5sha1_ID 133 
#define  br_sha1_ID 132 
#define  br_sha224_ID 131 
#define  br_sha256_ID 130 
#define  br_sha384_ID 129 
#define  br_sha512_ID 128 

const char *
hash_function_name(int id)
{
	switch (id) {
	case br_md5sha1_ID:  return "MD5+SHA-1";
	case br_md5_ID:      return "MD5";
	case br_sha1_ID:     return "SHA-1";
	case br_sha224_ID:   return "SHA-224";
	case br_sha256_ID:   return "SHA-256";
	case br_sha384_ID:   return "SHA-384";
	case br_sha512_ID:   return "SHA-512";
	default:
		return "unknown";
	}
}