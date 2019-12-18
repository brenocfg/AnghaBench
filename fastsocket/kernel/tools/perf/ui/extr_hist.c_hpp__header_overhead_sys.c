#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hpp__header_overhead_sys(struct perf_hpp *hpp)
{
	const char *fmt = symbol_conf.field_sep ? "%s" : "%7s";

	return scnprintf(hpp->buf, hpp->size, fmt, "sys");
}