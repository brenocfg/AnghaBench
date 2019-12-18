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
typedef  size_t uint8_t ;

/* Variables and functions */
 int TLC59401_CHANNELS ; 
 size_t TLC59401_LOOKUP_ENTRIES ; 
 int /*<<< orphan*/ ** lookupTable ; 
 int /*<<< orphan*/  pack12bit (size_t*,int,int /*<<< orphan*/ ) ; 

void TLC59401_GetCalibration(uint8_t index, uint8_t *values) {
    int i;
    if(index < TLC59401_LOOKUP_ENTRIES) {
        for(i = 0; i < TLC59401_CHANNELS; i++)
            pack12bit(values, i, lookupTable[i][index]);
    }
}