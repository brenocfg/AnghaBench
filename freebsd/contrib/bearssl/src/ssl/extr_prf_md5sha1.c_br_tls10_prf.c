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
typedef  int /*<<< orphan*/  br_tls_prf_seed_chunk ;

/* Variables and functions */
 int /*<<< orphan*/  br_md5_vtable ; 
 int /*<<< orphan*/  br_sha1_vtable ; 
 int /*<<< orphan*/  br_tls_phash (void*,size_t,int /*<<< orphan*/ *,unsigned char const*,size_t,char const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void
br_tls10_prf(void *dst, size_t len,
	const void *secret, size_t secret_len, const char *label,
	size_t seed_num, const br_tls_prf_seed_chunk *seed)
{
	const unsigned char *s1;
	size_t slen;

	s1 = secret;
	slen = (secret_len + 1) >> 1;
	memset(dst, 0, len);
	br_tls_phash(dst, len, &br_md5_vtable,
		s1, slen, label, seed_num, seed);
	br_tls_phash(dst, len, &br_sha1_vtable,
		s1 + secret_len - slen, slen, label, seed_num, seed);
}