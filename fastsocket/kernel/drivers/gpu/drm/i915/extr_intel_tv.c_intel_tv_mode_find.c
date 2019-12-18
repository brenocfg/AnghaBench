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
struct tv_mode {int dummy; } ;
struct intel_tv {int /*<<< orphan*/  tv_format; } ;

/* Variables and functions */
 struct tv_mode const* intel_tv_mode_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct tv_mode *
intel_tv_mode_find(struct intel_tv *intel_tv)
{
	return intel_tv_mode_lookup(intel_tv->tv_format);
}