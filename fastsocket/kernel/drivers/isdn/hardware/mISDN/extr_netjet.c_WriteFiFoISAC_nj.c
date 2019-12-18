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
struct tiger_hw {int auxd; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ NJ_AUXDATA ; 
 scalar_t__ NJ_ISAC_OFF ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outsb (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
WriteFiFoISAC_nj(void *p, u8 offset, u8 *data, int size)
{
	struct tiger_hw *card = p;

	card->auxd &= 0xfc;
	outb(card->auxd, card->base + NJ_AUXDATA);
	outsb(card->base + NJ_ISAC_OFF, data, size);
}