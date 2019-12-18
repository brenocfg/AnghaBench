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
typedef  int /*<<< orphan*/  u8 ;
struct nvidia_par {scalar_t__ IOBase; int /*<<< orphan*/  PCIO; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_RD08 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

u8 NVReadCrtc(struct nvidia_par *par, u8 index)
{
	VGA_WR08(par->PCIO, par->IOBase + 0x04, index);
	return (VGA_RD08(par->PCIO, par->IOBase + 0x05));
}