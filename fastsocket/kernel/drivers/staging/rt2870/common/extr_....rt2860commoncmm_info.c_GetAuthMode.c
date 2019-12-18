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
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__ Ndis802_11AuthModeAutoSwitch ; 
 scalar_t__ Ndis802_11AuthModeOpen ; 
 scalar_t__ Ndis802_11AuthModeShared ; 
 scalar_t__ Ndis802_11AuthModeWPA ; 
 scalar_t__ Ndis802_11AuthModeWPA1PSKWPA2PSK ; 
 scalar_t__ Ndis802_11AuthModeWPA1WPA2 ; 
 scalar_t__ Ndis802_11AuthModeWPA2 ; 
 scalar_t__ Ndis802_11AuthModeWPA2PSK ; 
 scalar_t__ Ndis802_11AuthModeWPANone ; 
 scalar_t__ Ndis802_11AuthModeWPAPSK ; 

CHAR *GetAuthMode(CHAR auth)
{
    if(auth == Ndis802_11AuthModeOpen)
    	return "OPEN";
    if(auth == Ndis802_11AuthModeShared)
    	return "SHARED";
	if(auth == Ndis802_11AuthModeAutoSwitch)
    	return "AUTOWEP";
    if(auth == Ndis802_11AuthModeWPA)
    	return "WPA";
    if(auth == Ndis802_11AuthModeWPAPSK)
    	return "WPAPSK";
    if(auth == Ndis802_11AuthModeWPANone)
    	return "WPANONE";
    if(auth == Ndis802_11AuthModeWPA2)
    	return "WPA2";
    if(auth == Ndis802_11AuthModeWPA2PSK)
    	return "WPA2PSK";
	if(auth == Ndis802_11AuthModeWPA1WPA2)
    	return "WPA1WPA2";
	if(auth == Ndis802_11AuthModeWPA1PSKWPA2PSK)
    	return "WPA1PSKWPA2PSK";

    	return "UNKNOW";
}