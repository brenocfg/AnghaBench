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
struct nvidia_par {int /*<<< orphan*/  PDIO; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_PEL_D ; 
 int /*<<< orphan*/  VGA_RD08 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 NVReadDacData(struct nvidia_par *par)
{
	return (VGA_RD08(par->PDIO, VGA_PEL_D));
}