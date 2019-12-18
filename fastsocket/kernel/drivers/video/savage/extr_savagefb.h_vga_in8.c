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
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  savage_in8 (int,struct savagefb_par*) ; 

__attribute__((used)) static inline u8 vga_in8(int addr, struct savagefb_par *par)
{
	return savage_in8(0x8000 + addr, par);
}