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
struct b44 {int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssb_write32 (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void bw32(const struct b44 *bp,
			unsigned long reg, unsigned long val)
{
	ssb_write32(bp->sdev, reg, val);
}