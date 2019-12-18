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
struct TYPE_6__ {TYPE_1__* input; } ;
struct TYPE_5__ {void** system; } ;
struct TYPE_4__ {int /*<<< orphan*/  padtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PAD6B ; 
 unsigned int MAX_INPUTS ; 
#define  SYSTEM_GG 131 
#define  SYSTEM_MCD 130 
#define  SYSTEM_MD 129 
 void* SYSTEM_MD_GAMEPAD ; 
 void* SYSTEM_MS_GAMEPAD ; 
#define  SYSTEM_SMS 128 
 TYPE_3__ config ; 
 TYPE_2__ input ; 
 int system_hw ; 

__attribute__((used)) static void configure_controls(void)
{
   unsigned i;

   switch (system_hw)
   {
      case SYSTEM_MD:
      case SYSTEM_MCD:
         for(i = 0; i < MAX_INPUTS; i++)
         {
            config.input[i].padtype = DEVICE_PAD6B;
         }	
         input.system[0] = SYSTEM_MD_GAMEPAD;
         input.system[1] = SYSTEM_MD_GAMEPAD;
         break;
      case SYSTEM_GG:
      case SYSTEM_SMS:
         input.system[0] = SYSTEM_MS_GAMEPAD;
         input.system[1] = SYSTEM_MS_GAMEPAD;
         break;
      default:
         break;
   }
}