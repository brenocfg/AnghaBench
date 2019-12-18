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
struct ptmx_ioctl {int dummy; } ;
struct knote {scalar_t__ kn_hook; } ;

/* Variables and functions */

__attribute__((used)) static struct ptmx_ioctl *
ptmx_knote_ioctl(struct knote *kn)
{
	return (struct ptmx_ioctl *)kn->kn_hook;
}