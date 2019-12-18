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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct input_dev {int keycodesize; scalar_t__ keycode; } ;

/* Variables and functions */

__attribute__((used)) static int input_fetch_keycode(struct input_dev *dev, int scancode)
{
	switch (dev->keycodesize) {
		case 1:
			return ((u8 *)dev->keycode)[scancode];

		case 2:
			return ((u16 *)dev->keycode)[scancode];

		default:
			return ((u32 *)dev->keycode)[scancode];
	}
}