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
typedef  int /*<<< orphan*/  br_shake_context ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t br_dec16be (unsigned char*) ; 
 int /*<<< orphan*/  br_shake_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_shake_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_shake_inject (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_shake_produce (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 size_t hextobin (unsigned char*,char const*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_SHAKE_MonteCarlo(int security_level,
	size_t minoutlen, size_t maxoutlen, const char *smsg, const char *sref)
{
	unsigned char out[250], ref[250];
	size_t len, rlen, outlen, range;
	int i, j;

	hextobin(out, smsg);
	outlen = maxoutlen;
	range = maxoutlen - minoutlen + 1;
	for (j = 0; j < 100; j ++) {
		for (i = 1; i < 1001; i ++) {
			br_shake_context sc;

			len = outlen;
			br_shake_init(&sc, security_level);
			br_shake_inject(&sc, out, 16);
			br_shake_flip(&sc);
			br_shake_produce(&sc, out, len);
			if (len < 16) {
				memset(out + len, 0, 16 - len);
			}
			outlen = minoutlen
				+ (br_dec16be(out + len - 2) % range);
		}
		printf(".");
		fflush(stdout);
	}
	rlen = hextobin(ref, sref);
	if (rlen != len) {
		fprintf(stderr, "MC: bad length (%u vs %u)\n",
			(unsigned)len, (unsigned)rlen);
		exit(EXIT_FAILURE);
	}
	check_equals("KAT MC", out, ref, len);
}