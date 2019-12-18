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
typedef  int uint8_t ;

/* Variables and functions */
#define  CategoryIDBusinessAndFinance 139 
#define  CategoryIDEmail 138 
#define  CategoryIDEntertainment 137 
#define  CategoryIDHealthAndFitness 136 
#define  CategoryIDIncomingCall 135 
#define  CategoryIDLocation 134 
#define  CategoryIDMissedCall 133 
#define  CategoryIDNews 132 
#define  CategoryIDOther 131 
#define  CategoryIDSchedule 130 
#define  CategoryIDSocial 129 
#define  CategoryIDVoicemail 128 

char *CategoryID_to_String(uint8_t CategoryID)
{
    char *Cidstr = NULL;
    switch(CategoryID) {
        case CategoryIDOther:
            Cidstr = "Other";
            break;
        case CategoryIDIncomingCall:
            Cidstr = "IncomingCall";
            break;
        case CategoryIDMissedCall:
            Cidstr = "MissedCall";
            break;
        case CategoryIDVoicemail:
            Cidstr = "Voicemail";
            break;
        case CategoryIDSocial:
            Cidstr = "Social";
            break;
        case CategoryIDSchedule:
            Cidstr = "Schedule";
            break;
        case CategoryIDEmail:
            Cidstr = "Email";
            break;
        case CategoryIDNews:
            Cidstr = "News";
            break;
        case CategoryIDHealthAndFitness:
            Cidstr = "HealthAndFitness";
            break;
        case CategoryIDBusinessAndFinance:
            Cidstr = "BusinessAndFinance";
            break;
        case CategoryIDLocation:
            Cidstr = "Location";
            break;
        case CategoryIDEntertainment:
            Cidstr = "Entertainment";
            break;
        default:
            Cidstr = "Unknown CategoryID";
            break;
    }
    return Cidstr;
}