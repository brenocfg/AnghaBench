#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_bits_t ;
struct TYPE_2__ {int buttons; } ;
typedef  TYPE_1__ ds3_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT256_SET_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_COPY16_PTR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RARCH_MENU_TOGGLE ; 

__attribute__((used)) static void ds3_get_buttons(void *data, input_bits_t *state)
{
   ds3_instance_t *pad = (ds3_instance_t *)data;

   if(pad)
   {
      BITS_COPY16_PTR(state, pad->buttons);

      if(pad->buttons & 0x10000)
         BIT256_SET_PTR(state, RARCH_MENU_TOGGLE);
   } else {
      BIT256_CLEAR_ALL_PTR(state);
   }
}