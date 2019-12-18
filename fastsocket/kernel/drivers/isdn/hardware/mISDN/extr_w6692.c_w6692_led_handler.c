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
struct w6692_hw {int fmask; scalar_t__ subtype; int xdata; } ;

/* Variables and functions */
 scalar_t__ W6692_USR ; 
 int /*<<< orphan*/  W_XDATA ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int) ; 
 int led ; 

__attribute__((used)) static void
w6692_led_handler(struct w6692_hw *card, int on)
{
	if ((!(card->fmask & led)) || card->subtype == W6692_USR)
		return;
	if (on) {
		card->xdata &= 0xfb;	/*  LED ON */
		WriteW6692(card, W_XDATA, card->xdata);
	} else {
		card->xdata |= 0x04;	/*  LED OFF */
		WriteW6692(card, W_XDATA, card->xdata);
	}
}