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

/* Variables and functions */
 int FFABS (int) ; 
 int MAX_DPCM ; 
 int ff_sqrt (int) ; 

__attribute__((used)) static unsigned char dpcm_predict(short *previous, short current)
{
    int diff;
    int negative;
    int result;
    int predicted;

    diff = current - *previous;

    negative = diff<0;
    diff = FFABS(diff);

    if (diff >= MAX_DPCM)
        result = 127;
    else {
        result = ff_sqrt(diff);
        result += diff > result*result+result;
    }

    /* See if this overflows */
 retry:
    diff = result*result;
    if (negative)
        diff = -diff;
    predicted = *previous + diff;

    /* If it overflows, back off a step */
    if (predicted > 32767 || predicted < -32768) {
        result--;
        goto retry;
    }

    /* Add the sign bit */
    result |= negative << 7;   //if (negative) result |= 128;

    *previous = predicted;

    return result;
}