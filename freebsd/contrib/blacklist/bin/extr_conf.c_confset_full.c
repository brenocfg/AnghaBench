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
struct confset {scalar_t__ cs_n; scalar_t__ cs_m; } ;

/* Variables and functions */

__attribute__((used)) static bool
confset_full(const struct confset *cs)
{
	return cs->cs_n == cs->cs_m;
}