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
typedef  int /*<<< orphan*/  br_hmac_key_context ;
typedef  int /*<<< orphan*/  br_hmac_context ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  br_hmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 
 size_t br_hmac_out (int /*<<< orphan*/ *,unsigned char*) ; 
 size_t br_hmac_outCT (int /*<<< orphan*/ *,unsigned char const*,size_t,size_t,size_t,unsigned char*) ; 
 int /*<<< orphan*/  br_hmac_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_HMAC_CT(const br_hash_class *digest_class,
	const void *key, size_t key_len, const void *data)
{
	br_hmac_key_context kc;
	br_hmac_context hc1, hc2;
	unsigned char buf1[64], buf2[64];
	size_t u, v;

	br_hmac_key_init(&kc, digest_class, key, key_len);

	for (u = 0; u < 2; u ++) {
		for (v = 0; v < 130; v ++) {
			size_t min_len, max_len;
			size_t w;

			min_len = v;
			max_len = v + 256;
			for (w = min_len; w <= max_len; w ++) {
				char tmp[30];
				size_t hlen1, hlen2;

				br_hmac_init(&hc1, &kc, 0);
				br_hmac_update(&hc1, data, u + w);
				hlen1 = br_hmac_out(&hc1, buf1);
				br_hmac_init(&hc2, &kc, 0);
				br_hmac_update(&hc2, data, u);
				hlen2 = br_hmac_outCT(&hc2,
					(const unsigned char *)data + u, w,
					min_len, max_len, buf2);
				if (hlen1 != hlen2) {
					fprintf(stderr, "HMAC length mismatch:"
						" %u / %u\n", (unsigned)hlen1,
						(unsigned)hlen2);
					exit(EXIT_FAILURE);
				}
				sprintf(tmp, "HMAC CT %u,%u,%u",
					(unsigned)u, (unsigned)v, (unsigned)w);
				check_equals(tmp, buf1, buf2, hlen1);
			}
		}
		printf(".");
		fflush(stdout);
	}
	printf(" ");
	fflush(stdout);
}