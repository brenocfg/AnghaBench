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
typedef  int /*<<< orphan*/  (* br_ghash ) (unsigned char*,unsigned char*,unsigned char*,int) ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,char*,double) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
test_speed_ghash_inner(char *name, br_ghash gh)
{
	unsigned char buf[8192], h[16], y[16];
	int i;
	long num;

	memset(buf, 'T', sizeof buf);
	memset(h, 'P', sizeof h);
	memset(y, 0, sizeof y);
	for (i = 0; i < 10; i ++) {
		gh(y, h, buf, sizeof buf);
	}
	num = 10;
	for (;;) {
		clock_t begin, end;
		double tt;
		long k;

		begin = clock();
		for (k = num; k > 0; k --) {
			gh(y, h, buf, sizeof buf);
		}
		end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		if (tt >= 2.0) {
			printf("%-30s %8.2f MB/s\n", name,
				((double)sizeof buf) * (double)num
				/ (tt * 1000000.0));
			fflush(stdout);
			return;
		}
		num <<= 1;
	}
}