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
struct socket_filter {int /*<<< orphan*/  sf_refcount; } ;

/* Variables and functions */

__attribute__((used)) static void
sflt_retain_locked(struct socket_filter	*filter)
{
	filter->sf_refcount++;
}