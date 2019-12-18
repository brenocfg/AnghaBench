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
struct TYPE_3__ {int /*<<< orphan*/  keyboard_state; } ;
typedef  TYPE_1__ qnx_input_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;

/* Variables and functions */
 scalar_t__ BIT_GET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int RETROK_LAST ; 
 unsigned int* rarch_keysym_lut ; 

__attribute__((used)) static bool qnx_keyboard_pressed(qnx_input_t *qnx, unsigned id)
{
    unsigned bit = rarch_keysym_lut[(enum retro_key)id];
    return id < RETROK_LAST && BIT_GET(qnx->keyboard_state, bit);
}