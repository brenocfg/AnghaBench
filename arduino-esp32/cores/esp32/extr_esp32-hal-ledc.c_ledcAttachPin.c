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
 scalar_t__ LEDC_HS_SIG_OUT0_IDX ; 
 scalar_t__ LEDC_LS_SIG_OUT0_IDX ; 
 int /*<<< orphan*/  OUTPUT ; 
 int /*<<< orphan*/  pinMatrixOutAttach (int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  pinMode (int,int /*<<< orphan*/ ) ; 

void ledcAttachPin(uint8_t pin, uint8_t chan)
{
    if(chan > 15) {
        return;
    }
    pinMode(pin, OUTPUT);
    pinMatrixOutAttach(pin, ((chan/8)?LEDC_LS_SIG_OUT0_IDX:LEDC_HS_SIG_OUT0_IDX) + (chan%8), false, false);
}