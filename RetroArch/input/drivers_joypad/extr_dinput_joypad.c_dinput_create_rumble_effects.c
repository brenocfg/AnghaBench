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
struct TYPE_6__ {int cAxes; int cbTypeSpecificParams; int dwFlags; int dwSize; int /*<<< orphan*/ * rglDirection; int /*<<< orphan*/ * rgdwAxes; TYPE_2__* lpvTypeSpecificParams; TYPE_1__* lpEnvelope; scalar_t__ dwStartDelay; scalar_t__ dwGain; int /*<<< orphan*/  dwDuration; scalar_t__ dwTriggerRepeatInterval; int /*<<< orphan*/  dwTriggerButton; } ;
struct dinput_joypad_data {int /*<<< orphan*/ * rumble_iface; TYPE_3__ rumble_props; int /*<<< orphan*/  joypad; } ;
struct TYPE_5__ {scalar_t__ lMagnitude; } ;
struct TYPE_4__ {int dwSize; int dwAttackLevel; int dwAttackTime; int dwFadeTime; scalar_t__ dwFadeLevel; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DIENVELOPE ;
typedef  int /*<<< orphan*/  DIEFFECT ;
typedef  TYPE_2__ DICONSTANTFORCE ;

/* Variables and functions */
 int /*<<< orphan*/  DIEB_NOTRIGGER ; 
 int DIEFF_CARTESIAN ; 
 int DIEFF_OBJECTOFFSETS ; 
 int /*<<< orphan*/  DIJOFS_X ; 
 int /*<<< orphan*/  DIJOFS_Y ; 
 scalar_t__ DI_OK ; 
 int /*<<< orphan*/ ******** GUID_ConstantForce ; 
 scalar_t__ IDirectInputDevice8_CreateEffect (int /*<<< orphan*/ ,int /*<<< orphan*/ *********,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 

__attribute__((used)) static void dinput_create_rumble_effects(struct dinput_joypad_data *pad)
{
   DIENVELOPE dienv;
   DICONSTANTFORCE dicf;
   LONG direction                            = 0;
   DWORD axis                                = DIJOFS_X;

   dicf.lMagnitude                           = 0;

   dienv.dwSize                              = sizeof(DIENVELOPE);
   dienv.dwAttackLevel                       = 5000;
   dienv.dwAttackTime                        = 250000;
   dienv.dwFadeLevel                         = 0;
   dienv.dwFadeTime                          = 250000;

   pad->rumble_props.cAxes                   = 1;
   pad->rumble_props.dwTriggerButton         = DIEB_NOTRIGGER;
   pad->rumble_props.dwTriggerRepeatInterval = 0;
   pad->rumble_props.cbTypeSpecificParams    = sizeof(DICONSTANTFORCE);
   pad->rumble_props.dwDuration              = INFINITE;
   pad->rumble_props.dwFlags                 = DIEFF_CARTESIAN |
      DIEFF_OBJECTOFFSETS;
   pad->rumble_props.dwGain                  = 0;
   pad->rumble_props.dwSize                  = sizeof(DIEFFECT);
   pad->rumble_props.dwStartDelay            = 0;
   pad->rumble_props.lpEnvelope              = &dienv;
   pad->rumble_props.lpvTypeSpecificParams   = &dicf;
   pad->rumble_props.rgdwAxes                = &axis;
   pad->rumble_props.rglDirection            = &direction;

#ifdef __cplusplus
   if (IDirectInputDevice8_CreateEffect(pad->joypad, GUID_ConstantForce,
         &pad->rumble_props, &pad->rumble_iface[0], NULL) != DI_OK)
      RARCH_WARN("[DINPUT]: Strong rumble unavailable.\n");
#else
   if (IDirectInputDevice8_CreateEffect(pad->joypad, &GUID_ConstantForce,
         &pad->rumble_props, &pad->rumble_iface[0], NULL) != DI_OK)
      RARCH_WARN("[DINPUT]: Strong rumble unavailable.\n");
#endif

   axis = DIJOFS_Y;

#ifdef __cplusplus
   if (IDirectInputDevice8_CreateEffect(pad->joypad, GUID_ConstantForce,
         &pad->rumble_props, &pad->rumble_iface[1], NULL) != DI_OK)
      RARCH_WARN("[DINPUT]: Weak rumble unavailable.\n");
#else
   if (IDirectInputDevice8_CreateEffect(pad->joypad, &GUID_ConstantForce,
         &pad->rumble_props, &pad->rumble_iface[1], NULL) != DI_OK)
      RARCH_WARN("[DINPUT]: Weak rumble unavailable.\n");
#endif
}