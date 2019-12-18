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
struct mbcs_soft {scalar_t__ mmr_base; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t mbcs_pioaddr(struct mbcs_soft *soft, uint64_t offset)
{
	uint64_t mmr_base;

	mmr_base = (uint64_t) (soft->mmr_base + offset);

	return mmr_base;
}