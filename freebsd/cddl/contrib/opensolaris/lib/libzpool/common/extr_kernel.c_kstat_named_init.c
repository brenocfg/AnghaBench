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
typedef  int /*<<< orphan*/  uchar_t ;
typedef  int /*<<< orphan*/  kstat_named_t ;

/* Variables and functions */

void
kstat_named_init(kstat_named_t *knp, const char *name, uchar_t type)
{}