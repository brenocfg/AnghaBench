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
struct TYPE_3__ {int SubType; int Flags; } ;
typedef  TYPE_1__ XINPUT_CAPABILITIES ;

/* Variables and functions */
 int XINPUT_CAPS_WIRELESS ; 
#define  XINPUT_DEVSUBTYPE_ARCADE_STICK 134 
#define  XINPUT_DEVSUBTYPE_DANCE_PAD 133 
#define  XINPUT_DEVSUBTYPE_DRUM_KIT 132 
#define  XINPUT_DEVSUBTYPE_FLIGHT_STICK 131 
#define  XINPUT_DEVSUBTYPE_GAMEPAD 130 
#define  XINPUT_DEVSUBTYPE_GUITAR 129 
#define  XINPUT_DEVSUBTYPE_WHEEL 128 

__attribute__((used)) static const char* getDeviceDescription(const XINPUT_CAPABILITIES* xic)
{
    switch (xic->SubType)
    {
        case XINPUT_DEVSUBTYPE_WHEEL:
            return "XInput Wheel";
        case XINPUT_DEVSUBTYPE_ARCADE_STICK:
            return "XInput Arcade Stick";
        case XINPUT_DEVSUBTYPE_FLIGHT_STICK:
            return "XInput Flight Stick";
        case XINPUT_DEVSUBTYPE_DANCE_PAD:
            return "XInput Dance Pad";
        case XINPUT_DEVSUBTYPE_GUITAR:
            return "XInput Guitar";
        case XINPUT_DEVSUBTYPE_DRUM_KIT:
            return "XInput Drum Kit";
        case XINPUT_DEVSUBTYPE_GAMEPAD:
        {
            if (xic->Flags & XINPUT_CAPS_WIRELESS)
                return "Wireless Xbox 360 Controller";
            else
                return "Xbox 360 Controller";
        }
    }

    return "Unknown XInput Device";
}