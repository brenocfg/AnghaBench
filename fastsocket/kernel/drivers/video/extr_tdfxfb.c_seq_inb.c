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
typedef  int /*<<< orphan*/  u32 ;
struct tdfx_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_D ; 
 int /*<<< orphan*/  SEQ_I ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  vga_inb (struct tdfx_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_outb (struct tdfx_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 seq_inb(struct tdfx_par *par, u32 idx)
{
	vga_outb(par, SEQ_I, idx);
	mb();
	return vga_inb(par, SEQ_D);
}