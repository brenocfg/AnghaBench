#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u8_t ;
typedef  int u32_t ;
struct TYPE_2__ {int tick; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfGenerateRandomBSSID(zdev_t* dev, u8_t *MACAddr, u8_t *BSSID)
{
    //ULONGLONG   time;
    u32_t time;

    zmw_get_wlan_dev(dev);

    time = wd->tick;

    //
    // Initialize the random BSSID to be the same as MAC address.
    //

    // RtlCopyMemory(BSSID, MACAddr, sizeof(DOT11_MAC_ADDRESS));
    zfMemoryCopy(BSSID, MACAddr, 6);

    //
    // Get the system time in 10 millisecond.
    //

    // NdisGetCurrentSystemTime((PLARGE_INTEGER)&time);
    // time /= 100000;

    //
    // Randomize the first 4 bytes of BSSID.
    //

    BSSID[0] ^= (u8_t)(time & 0xff);
    BSSID[0] &= ~0x01;              // Turn off multicast bit
    BSSID[0] |= 0x02;               // Turn on local bit

    time >>= 8;
    BSSID[1] ^= (u8_t)(time & 0xff);

    time >>= 8;
    BSSID[2] ^= (u8_t)(time & 0xff);

    time >>= 8;
    BSSID[3] ^= (u8_t)(time & 0xff);
}