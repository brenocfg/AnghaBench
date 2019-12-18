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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 int ZM_WLAN_EID_EXTENDED_HT_CAPABILITY ; 
 int ZM_WLAN_EID_HT_CAPABILITY ; 
 int ZM_WLAN_EID_WPA_IE ; 
 int /*<<< orphan*/  zfMemoryMove (int*,int*,scalar_t__) ; 

u16_t zfRemoveElement(zdev_t* dev, u8_t* buf, u16_t size, u8_t eid)
{
    u16_t offset = 0;
    u16_t elen;
    u8_t  HTEid = 0;
    u8_t  oui[4] = {0x00, 0x50, 0xf2, 0x01};
    u8_t  oui11n[3] = {0x00,0x90,0x4C};
    u8_t  HTType = 0;

    if ((eid == ZM_WLAN_EID_HT_CAPABILITY) ||
        (eid == ZM_WLAN_EID_EXTENDED_HT_CAPABILITY))
    {
        HTEid = eid;
        eid = ZM_WLAN_EID_WPA_IE;
        HTType = 1;
    }

    while (offset < size)
    {
        elen = *(buf+offset+1);

        if (*(buf+offset) == eid)
        {
            if ( eid == ZM_WLAN_EID_WPA_IE )
            {
                if ( (HTType == 0)
                     && (*(buf+offset+2) == oui[0])
                     && (*(buf+offset+3) == oui[1])
                     && (*(buf+offset+4) == oui[2])
                     && (*(buf+offset+5) == oui[3]) )
                {
                    zfMemoryMove(buf+offset, buf+offset+elen+2, size-offset-elen-2);
                    return (size-elen-2);
                }

                if ( (HTType == 1)
                    && (*(buf+offset+2) == oui11n[0])
                    && (*(buf+offset+3) == oui11n[1])
                    && (*(buf+offset+4) == oui11n[2])
                    && (*(buf+offset+5) == HTEid) )
                {
                    zfMemoryMove(buf+offset, buf+offset+elen+2, size-offset-elen-2);
                    return (size-elen-2);
                }
            }
            else
            {
                zfMemoryMove(buf+offset, buf+offset+elen+2, size-offset-elen-2);
                return (size-elen-2);
            }
        }

        offset += (elen+2);
    }

    return size;
}