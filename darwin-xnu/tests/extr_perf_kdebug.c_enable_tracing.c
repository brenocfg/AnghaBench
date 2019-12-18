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
 int /*<<< orphan*/  KDEBUG_ENABLE_TRACE ; 
 int /*<<< orphan*/  _sysctl_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_tracing(bool value) {
	_sysctl_enable(value ? KDEBUG_ENABLE_TRACE : 0);
}