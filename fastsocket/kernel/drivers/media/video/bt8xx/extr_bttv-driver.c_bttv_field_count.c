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
struct bttv {scalar_t__ field_count; scalar_t__ users; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_INT_MASK ; 
 int /*<<< orphan*/  BT848_INT_VSYNC ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bttv_field_count(struct bttv *btv)
{
	int need_count = 0;

	if (btv->users)
		need_count++;

	if (need_count) {
		/* start field counter */
		btor(BT848_INT_VSYNC,BT848_INT_MASK);
	} else {
		/* stop field counter */
		btand(~BT848_INT_VSYNC,BT848_INT_MASK);
		btv->field_count = 0;
	}
}