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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TXLO_ENTRIES ; 
 int /*<<< orphan*/  typhoon_inc_index (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
typhoon_inc_tx_index(u32 *index, const int count)
{
	/* if we start using the Hi Tx ring, this needs updateing */
	typhoon_inc_index(index, count, TXLO_ENTRIES);
}