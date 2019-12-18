#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* data; size_t len; } ;
typedef  TYPE_1__ br_tls_prf_seed_chunk ;
typedef  int /*<<< orphan*/  (* br_tls_prf_impl ) (unsigned char*,size_t,unsigned char*,size_t,char const*,int,TYPE_1__*) ;

/* Variables and functions */
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 size_t hextobin (unsigned char*,char const*) ; 

__attribute__((used)) static void
do_KAT_PRF(br_tls_prf_impl prf,
	const char *ssecret, const char *label, const char *sseed,
	const char *sref)
{
	unsigned char secret[100], seed[100], ref[500], out[500];
	size_t secret_len, seed_len, ref_len;
	br_tls_prf_seed_chunk chunks[2];

	secret_len = hextobin(secret, ssecret);
	seed_len = hextobin(seed, sseed);
	ref_len = hextobin(ref, sref);

	chunks[0].data = seed;
	chunks[0].len = seed_len;
	prf(out, ref_len, secret, secret_len, label, 1, chunks);
	check_equals("TLS PRF KAT 1", out, ref, ref_len);

	chunks[0].data = seed;
	chunks[0].len = seed_len;
	chunks[1].data = NULL;
	chunks[1].len = 0;
	prf(out, ref_len, secret, secret_len, label, 2, chunks);
	check_equals("TLS PRF KAT 2", out, ref, ref_len);

	chunks[0].data = NULL;
	chunks[0].len = 0;
	chunks[1].data = seed;
	chunks[1].len = seed_len;
	prf(out, ref_len, secret, secret_len, label, 2, chunks);
	check_equals("TLS PRF KAT 3", out, ref, ref_len);

	chunks[0].data = seed;
	chunks[0].len = seed_len >> 1;
	chunks[1].data = seed + chunks[0].len;
	chunks[1].len = seed_len - chunks[0].len;
	prf(out, ref_len, secret, secret_len, label, 2, chunks);
	check_equals("TLS PRF KAT 4", out, ref, ref_len);
}