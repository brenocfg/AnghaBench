#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int) ; 
 scalar_t__ btsnd_hcic_write_voice_settings (int) ; 

tBTM_STATUS BTM_WriteVoiceSettings(UINT16 settings)
{
    BTM_TRACE_EVENT ("BTM: BTM_WriteVoiceSettings: Settings: 0x%04x.", settings);

    /* Send the HCI command */
    if (btsnd_hcic_write_voice_settings ((UINT16)(settings & 0x03ff))) {
        return (BTM_SUCCESS);
    }

    return (BTM_NO_RESOURCES);
}