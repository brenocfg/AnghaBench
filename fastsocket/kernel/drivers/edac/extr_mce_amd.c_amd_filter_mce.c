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
typedef  int u8 ;
struct mce {int status; int bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  report_gart_errors ; 

__attribute__((used)) static bool amd_filter_mce(struct mce *m)
{
	u8 xec = (m->status >> 16) & 0x1f;

	/*
	 * NB GART TLB error reporting is disabled by default.
	 */
	if (m->bank == 4 && xec == 0x5 && !report_gart_errors)
		return true;

	return false;
}