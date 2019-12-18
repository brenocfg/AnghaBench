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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static bool same_hdr(const void *_d0, const void *_d1)
{
	const uint32_t *d0 = _d0;
	const uint32_t *d1 = _d1;

	/* BUG_ON((unsigned long)d0 & 3 || (unsigned long)d1 & 3)) */
	return !((d0[0] ^ d1[0]) |			/* FC + DU */
		 (d0[1] ^ d1[1]) |			/* addr1 */
		 (d0[2] ^ d1[2]) | (d0[3] ^ d1[3]) |	/* addr2 + addr3 */
		 (d0[4] ^ d1[4]));			/* addr3 */
}