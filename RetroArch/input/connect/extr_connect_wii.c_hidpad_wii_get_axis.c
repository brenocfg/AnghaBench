#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int value; } ;
struct TYPE_13__ {int value; } ;
struct TYPE_15__ {TYPE_5__ y; TYPE_4__ x; } ;
struct TYPE_11__ {int value; } ;
struct TYPE_10__ {int value; } ;
struct TYPE_12__ {TYPE_2__ y; TYPE_1__ x; } ;
struct TYPE_16__ {TYPE_6__ rjs; TYPE_3__ ljs; } ;
struct TYPE_17__ {TYPE_7__ classic; } ;
struct TYPE_18__ {int type; TYPE_8__ cc; } ;
struct connect_wii_wiimote_t {TYPE_9__ exp; } ;
typedef  int int16_t ;

/* Variables and functions */
#define  EXP_CLASSIC 128 

__attribute__((used)) static int16_t hidpad_wii_get_axis(void *data, unsigned axis)
{
   struct connect_wii_wiimote_t* device = (struct connect_wii_wiimote_t*)data;

   if (!device)
      return 0;

   switch (device->exp.type)
   {
      case EXP_CLASSIC:
         switch (axis)
         {
            case 0:
               return device->exp.cc.classic.ljs.x.value * 0x7FFF;
            case 1:
               return device->exp.cc.classic.ljs.y.value * 0x7FFF;
            case 2:
               return device->exp.cc.classic.rjs.x.value * 0x7FFF;
            case 3:
               return device->exp.cc.classic.rjs.y.value * 0x7FFF;
         }
         break;
      default:
         break;
   }

   return 0;
}