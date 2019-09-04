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
struct resolvconf {int dummy; } ;

/* Variables and functions */
 scalar_t__ __get_resolv_conf (struct resolvconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __res_msend_rc (int,unsigned char const* const*,int const*,unsigned char* const*,int*,int,struct resolvconf*) ; 

int __res_msend(int nqueries, const unsigned char *const *queries,
	const int *qlens, unsigned char *const *answers, int *alens, int asize)
{
	struct resolvconf conf;
	if (__get_resolv_conf(&conf, 0, 0) < 0) return -1;
	return __res_msend_rc(nqueries, queries, qlens, answers, alens, asize, &conf);
}