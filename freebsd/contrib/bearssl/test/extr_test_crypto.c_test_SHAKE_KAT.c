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
 int /*<<< orphan*/  br_shake_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_shake_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_shake_inject (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_shake_produce (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  check_equals (char*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 size_t hextobin (unsigned char*,char const* const) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_SHAKE_KAT(int security_level, const char *const *kat)
{
	size_t u;

	for (u = 0; kat[u] != NULL; u += 2) {
		unsigned char msg[250], out[250], ref[250];
		size_t msg_len, out_len, v;
		br_shake_context sc;

		msg_len = hextobin(msg, kat[u]);
		out_len = hextobin(ref, kat[u + 1]);
		br_shake_init(&sc, security_level);
		br_shake_inject(&sc, msg, msg_len);
		br_shake_flip(&sc);
		br_shake_produce(&sc, out, out_len);
		check_equals("KAT 1", out, ref, out_len);

		br_shake_init(&sc, security_level);
		for (v = 0; v < msg_len; v ++) {
			br_shake_inject(&sc, msg + v, 1);
		}
		br_shake_flip(&sc);
		br_shake_produce(&sc, out, out_len);
		check_equals("KAT 2", out, ref, out_len);

		br_shake_init(&sc, security_level);
		br_shake_inject(&sc, msg, msg_len);
		br_shake_flip(&sc);
		for (v = 0; v < out_len; v ++) {
			unsigned char x;

			br_shake_produce(&sc, &x, 1);
			if (x != ref[v]) {
				fprintf(stderr, "KAT 3 (byte %u)\n",
					(unsigned)v);
				exit(EXIT_FAILURE);
			}
		}

		printf(".");
		fflush(stdout);
	}
}