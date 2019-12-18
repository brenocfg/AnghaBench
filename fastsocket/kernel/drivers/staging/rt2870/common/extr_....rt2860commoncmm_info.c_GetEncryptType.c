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
 scalar_t__ Ndis802_11Encryption2Enabled ; 
 scalar_t__ Ndis802_11Encryption3Enabled ; 
 scalar_t__ Ndis802_11Encryption4Enabled ; 
 scalar_t__ Ndis802_11WEPDisabled ; 
 scalar_t__ Ndis802_11WEPEnabled ; 

CHAR *GetEncryptType(CHAR enc)
{
    if(enc == Ndis802_11WEPDisabled)
        return "NONE";
    if(enc == Ndis802_11WEPEnabled)
    	return "WEP";
    if(enc == Ndis802_11Encryption2Enabled)
    	return "TKIP";
    if(enc == Ndis802_11Encryption3Enabled)
    	return "AES";
	if(enc == Ndis802_11Encryption4Enabled)
    	return "TKIPAES";
    else
    	return "UNKNOW";
}