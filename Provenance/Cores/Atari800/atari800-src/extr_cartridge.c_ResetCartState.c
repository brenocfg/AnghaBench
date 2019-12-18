#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int state; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
#define  CARTRIDGE_AST_32 131 
#define  CARTRIDGE_ATMAX_1024 130 
#define  CARTRIDGE_MEGA_4096 129 
#define  CARTRIDGE_OSS_034M_16 128 

__attribute__((used)) static void ResetCartState(CARTRIDGE_image_t *cart)
{
	switch (cart->type) {
	case CARTRIDGE_OSS_034M_16:
		cart->state = 1;
		break;
	case CARTRIDGE_ATMAX_1024:
		cart->state = 0x7f;
		break;
	case CARTRIDGE_AST_32:
		/* A special value of 0x10000 indicates the cartridge is
		   enabled and the current bank is 0. */
		cart->state = 0x10000;
		break;
	case CARTRIDGE_MEGA_4096:
		cart->state = 254;
		break;
	default:
		cart->state = 0;
	}
}