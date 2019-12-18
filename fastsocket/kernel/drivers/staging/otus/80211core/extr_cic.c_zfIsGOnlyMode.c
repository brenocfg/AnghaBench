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
 int* zg11gRateTbl ; 

u8_t zfIsGOnlyMode(zdev_t* dev, u16_t  frequency, u8_t* rateArray)
{
    u8_t length = rateArray[1];
    u8_t i, j;

    if (frequency < 3000) {
        for (i = 2; i < length+2; i++) {
            for (j = 0; j < 8; j++) {
                if ( ((rateArray[i] & 0x7f) == zg11gRateTbl[j])
                     && (rateArray[i] & 0x80) ) {
                    return 1;
                }
            }
        }
    }

    return 0;
}