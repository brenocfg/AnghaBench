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
typedef  int int16_t ;
struct TYPE_3__ {int* data; int** analog_state; } ;
typedef  TYPE_1__ gca_pad_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * axes ; 

__attribute__((used)) static void wiiu_gca_update_analog_state(gca_pad_t *pad)
{
   int pad_axis;
   int16_t interpolated;
   unsigned stick, axis;

   /* GameCube analog axis are 8-bit unsigned, where 128/128 is center.
    * So, we subtract 128 to get a signed, 0-based value and then mulitply
    * by 256 to get the 16-bit range RetroArch expects. */
   for (pad_axis = 0; pad_axis < 4; pad_axis++)
   {
      axis = pad_axis % 2 ? 0 : 1;
      stick = pad_axis / 2;
      interpolated = pad->data[3 + pad_axis];
      /* libretro requires "up" to be negative, so we invert the y axis */
      interpolated = (axis) ?
         ((interpolated - 128) * 256) :
         ((interpolated - 128) * -256);

      pad->analog_state[stick][axis] = interpolated;
#if 0
      RARCH_LOG("%s: %d\n", axes[pad_axis], interpolated);
#endif
   }
}