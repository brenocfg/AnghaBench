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
typedef  int u32 ;
typedef  int u16 ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_STAT ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par const*) ; 

__attribute__((used)) static inline void wait_for_fifo(u16 entries, const struct atyfb_par *par)
{
	while ((aty_ld_le32(FIFO_STAT, par) & 0xffff) >
	       ((u32) (0x8000 >> entries)));
}