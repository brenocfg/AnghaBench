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
typedef  int u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfHpUpdateQosParameter (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 

void zfUpdateDefaultQosParameter(zdev_t* dev, u8_t mode)
{
    u16_t cwmin[5];
    u16_t cwmax[5];
    u16_t aifs[5];
    u16_t txop[5];

    /* WMM parameter for STA */
    /* Best Effor */
    cwmin[0] = 15;
    cwmax[0] = 1023;
    aifs[0] = 3 * 9 + 10;
    txop[0] = 0;
    /* Back Ground */
    cwmin[1] = 15;
    cwmax[1] = 1023;
    aifs[1] = 7 * 9 + 10;
    txop[1] = 0;
    /* VIDEO */
    cwmin[2] = 7;
    cwmax[2] = 15;
    aifs[2] = 2 * 9 + 10;
    txop[2] = 94;
    /* VOICE */
    cwmin[3] = 3;
    cwmax[3] = 7;
    aifs[3] = 2 * 9 + 10;
    txop[3] = 47;
    /* Special TxQ */
    cwmin[4] = 3;
    cwmax[4] = 7;
    aifs[4] = 2 * 9 + 10;
    txop[4] = 0;

    /* WMM parameter for AP */
    if (mode == 1)
    {
        cwmax[0] = 63;
        aifs[3] = 1 * 9 + 10;
        aifs[4] = 1 * 9 + 10;
    }
    zfHpUpdateQosParameter(dev, cwmin, cwmax, aifs, txop);
}