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
 unsigned int SCD_BASE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline unsigned int SCD_QUEUE_RDPTR(unsigned int chnl)
{
	if (chnl < 20)
		return SCD_BASE + 0x68 + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	return SCD_BASE + 0x2B4 + (chnl - 20) * 4;
}