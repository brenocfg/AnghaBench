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
typedef  scalar_t__ clock_t ;
typedef  int /*<<< orphan*/  br_shake_context ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  br_shake_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_shake_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_shake_inject (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  br_shake_produce (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,int,double) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_speed_shake_inner(int security_level)
{
	unsigned char buf[8192];
	br_shake_context sc;
	int i;
	long num;

	memset(buf, 'D', sizeof buf);
	br_shake_init(&sc, security_level);
	for (i = 0; i < 10; i ++) {
		br_shake_inject(&sc, buf, sizeof buf);
	}
	num = 10;
	for (;;) {
		clock_t begin, end;
		double tt;
		long k;

		begin = clock();
		for (k = num; k > 0; k --) {
			br_shake_inject(&sc, buf, sizeof buf);
		}
		end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		if (tt >= 2.0) {
			printf("SHAKE%-3d (inject)              %8.2f MB/s\n",
				security_level,
				((double)sizeof buf) * (double)num
				/ (tt * 1000000.0));
			fflush(stdout);
			break;
		}
		num <<= 1;
	}

	br_shake_flip(&sc);
	for (i = 0; i < 10; i ++) {
		br_shake_produce(&sc, buf, sizeof buf);
	}

	num = 10;
	for (;;) {
		clock_t begin, end;
		double tt;
		long k;

		begin = clock();
		for (k = num; k > 0; k --) {
			br_shake_produce(&sc, buf, sizeof buf);
		}
		end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		if (tt >= 2.0) {
			printf("SHAKE%-3d (produce)             %8.2f MB/s\n",
				security_level,
				((double)sizeof buf) * (double)num
				/ (tt * 1000000.0));
			fflush(stdout);
			break;
		}
		num <<= 1;
	}
}