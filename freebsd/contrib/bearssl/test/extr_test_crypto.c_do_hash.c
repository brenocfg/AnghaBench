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
typedef  int /*<<< orphan*/  br_sha512_context ;
typedef  int /*<<< orphan*/  br_sha384_context ;
typedef  int /*<<< orphan*/  br_sha256_context ;
typedef  int /*<<< orphan*/  br_sha224_context ;
typedef  int /*<<< orphan*/  br_sha1_context ;
typedef  int /*<<< orphan*/  br_md5_context ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
#define  br_md5_ID 133 
 int /*<<< orphan*/  br_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_md5_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_md5_update (int /*<<< orphan*/ *,void const*,size_t) ; 
#define  br_sha1_ID 132 
 int /*<<< orphan*/  br_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sha1_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_sha1_update (int /*<<< orphan*/ *,void const*,size_t) ; 
#define  br_sha224_ID 131 
 int /*<<< orphan*/  br_sha224_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sha224_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_sha224_update (int /*<<< orphan*/ *,void const*,size_t) ; 
#define  br_sha256_ID 130 
 int /*<<< orphan*/  br_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sha256_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_sha256_update (int /*<<< orphan*/ *,void const*,size_t) ; 
#define  br_sha384_ID 129 
 int /*<<< orphan*/  br_sha384_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sha384_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_sha384_update (int /*<<< orphan*/ *,void const*,size_t) ; 
#define  br_sha512_ID 128 
 int /*<<< orphan*/  br_sha512_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sha512_out (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  br_sha512_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t
do_hash(int id, const void *data, size_t len, void *out)
{
	br_md5_context cmd5;
	br_sha1_context csha1;
	br_sha224_context csha224;
	br_sha256_context csha256;
	br_sha384_context csha384;
	br_sha512_context csha512;

	switch (id) {
	case br_md5_ID:
		br_md5_init(&cmd5);
		br_md5_update(&cmd5, data, len);
		br_md5_out(&cmd5, out);
		return 16;
	case br_sha1_ID:
		br_sha1_init(&csha1);
		br_sha1_update(&csha1, data, len);
		br_sha1_out(&csha1, out);
		return 20;
	case br_sha224_ID:
		br_sha224_init(&csha224);
		br_sha224_update(&csha224, data, len);
		br_sha224_out(&csha224, out);
		return 28;
	case br_sha256_ID:
		br_sha256_init(&csha256);
		br_sha256_update(&csha256, data, len);
		br_sha256_out(&csha256, out);
		return 32;
	case br_sha384_ID:
		br_sha384_init(&csha384);
		br_sha384_update(&csha384, data, len);
		br_sha384_out(&csha384, out);
		return 48;
	case br_sha512_ID:
		br_sha512_init(&csha512);
		br_sha512_update(&csha512, data, len);
		br_sha512_out(&csha512, out);
		return 64;
	default:
		fprintf(stderr, "Uknown hash function: %d\n", id);
		exit(EXIT_FAILURE);
		return 0;
	}
}