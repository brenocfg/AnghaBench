#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int btns; } ;
struct TYPE_5__ {TYPE_1__ classic; } ;
struct TYPE_6__ {TYPE_2__ cc; } ;
struct connect_wii_wiimote_t {int btns; TYPE_3__ exp; } ;
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_COPY32_PTR (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hidpad_wii_get_buttons(void *data, input_bits_t *state)
{
	struct connect_wii_wiimote_t* device = (struct connect_wii_wiimote_t*)data;
	if ( device )
	{
		/* TODO/FIXME - Broken? this doesn't match retropad! */
		uint32_t b = device->btns | (device->exp.cc.classic.btns << 16);
		BITS_COPY32_PTR(state, b);
	}
}