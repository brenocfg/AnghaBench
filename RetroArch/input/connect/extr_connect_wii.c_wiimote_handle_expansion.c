#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  classic; } ;
struct TYPE_4__ {int type; TYPE_1__ cc; } ;
struct connect_wii_wiimote_t {TYPE_2__ exp; } ;

/* Variables and functions */
#define  EXP_CLASSIC 128 
 int /*<<< orphan*/  classic_ctrl_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiimote_handle_expansion(struct connect_wii_wiimote_t* wm, uint8_t* msg)
{
   switch (wm->exp.type)
   {
      case EXP_CLASSIC:
         classic_ctrl_event(&wm->exp.cc.classic, msg);
         break;
      default:
         break;
   }
}