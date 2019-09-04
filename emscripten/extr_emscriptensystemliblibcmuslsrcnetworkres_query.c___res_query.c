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

/* Variables and functions */
 int __res_mkquery (int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int __res_send (unsigned char*,int,unsigned char*,int) ; 

int __res_query(const char *name, int class, int type, unsigned char *dest, int len)
{
	unsigned char q[280];
	int ql = __res_mkquery(0, name, class, type, 0, 0, 0, q, sizeof q);
	if (ql < 0) return ql;
	return __res_send(q, ql, dest, len);
}