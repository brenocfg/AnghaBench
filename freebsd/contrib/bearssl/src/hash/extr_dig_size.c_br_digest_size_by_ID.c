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
 size_t br_md5_SIZE ; 
#define  br_md5sha1_ID 133 
#define  br_sha1_ID 132 
 size_t br_sha1_SIZE ; 
#define  br_sha224_ID 131 
 size_t br_sha224_SIZE ; 
#define  br_sha256_ID 130 
 size_t br_sha256_SIZE ; 
#define  br_sha384_ID 129 
 size_t br_sha384_SIZE ; 
#define  br_sha512_ID 128 
 size_t br_sha512_SIZE ; 

size_t
br_digest_size_by_ID(int digest_id)
{
	switch (digest_id) {
	case br_md5sha1_ID:
		return br_md5_SIZE + br_sha1_SIZE;
	case br_md5_ID:
		return br_md5_SIZE;
	case br_sha1_ID:
		return br_sha1_SIZE;
	case br_sha224_ID:
		return br_sha224_SIZE;
	case br_sha256_ID:
		return br_sha256_SIZE;
	case br_sha384_ID:
		return br_sha384_SIZE;
	case br_sha512_ID:
		return br_sha512_SIZE;
	default:
		/* abort(); */
		return 0;
	}
}