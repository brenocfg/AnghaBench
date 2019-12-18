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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned long long) ; 
 scalar_t__ dt_stddev (scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int
dt_print_stddev(dtrace_hdl_t *dtp, FILE *fp, caddr_t addr,
    size_t size, uint64_t normal)
{
	/* LINTED - alignment */
	uint64_t *data = (uint64_t *)addr;

	return (dt_printf(dtp, fp, " %16llu", data[0] ?
	    (unsigned long long) dt_stddev(data, normal) : 0));
}