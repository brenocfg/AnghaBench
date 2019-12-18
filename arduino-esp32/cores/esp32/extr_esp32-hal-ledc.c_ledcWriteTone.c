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
 double _ledcSetupTimerFreq (int,double,int) ; 
 int /*<<< orphan*/  ledcWrite (int,int) ; 

double ledcWriteTone(uint8_t chan, double freq)
{
    if(chan > 15) {
        return 0;
    }
    if(!freq) {
        ledcWrite(chan, 0);
        return 0;
    }
    double res_freq = _ledcSetupTimerFreq(chan, freq, 10);
    ledcWrite(chan, 0x1FF);
    return res_freq;
}