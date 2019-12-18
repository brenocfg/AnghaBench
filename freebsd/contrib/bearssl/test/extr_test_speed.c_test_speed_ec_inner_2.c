#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ clock_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* mulgen ) (unsigned char*,unsigned char*,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ br_ec_impl ;
struct TYPE_6__ {size_t order_len; int /*<<< orphan*/  curve; int /*<<< orphan*/  order; } ;
typedef  TYPE_2__ br_ec_curve_def ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  br_i31_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  br_i31_decode_reduce (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_i31_encode (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,double) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_speed_ec_inner_2(const char *name,
	const br_ec_impl *impl, const br_ec_curve_def *cd)
{
	unsigned char bx[80], U[160];
	uint32_t x[22], n[22];
	size_t nlen;
	int i;
	long num;

	nlen = cd->order_len;
	br_i31_decode(n, cd->order, nlen);
	memset(bx, 'T', sizeof bx);
	br_i31_decode_reduce(x, bx, sizeof bx, n);
	br_i31_encode(bx, nlen, x);
	for (i = 0; i < 10; i ++) {
		impl->mulgen(U, bx, nlen, cd->curve);
	}
	num = 10;
	for (;;) {
		clock_t begin, end;
		double tt;
		long k;

		begin = clock();
		for (k = num; k > 0; k --) {
			impl->mulgen(U, bx, nlen, cd->curve);
		}
		end = clock();
		tt = (double)(end - begin) / CLOCKS_PER_SEC;
		if (tt >= 2.0) {
			printf("%-30s %8.2f mul/s\n", name,
				(double)num / tt);
			fflush(stdout);
			break;
		}
		num <<= 1;
	}
}