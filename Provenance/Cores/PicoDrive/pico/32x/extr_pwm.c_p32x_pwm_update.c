#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* regs; } ;
struct TYPE_3__ {short* pwm; scalar_t__* pwm_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_PWM ; 
 TYPE_2__ Pico32x ; 
 TYPE_1__* Pico32xMem ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  consume_fifo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int pwm_ptr ; 
 int pwm_silent ; 

void p32x_pwm_update(int *buf32, int length, int stereo)
{
  short *pwmb;
  int step;
  int p = 0;
  int xmd;

  consume_fifo(NULL, SekCyclesDone());

  xmd = Pico32x.regs[0x30 / 2] & 0x0f;
  if (xmd == 0 || xmd == 0x06 || xmd == 0x09 || xmd == 0x0f)
    goto out; // invalid?
  if (pwm_silent)
    return;

  step = (pwm_ptr << 16) / length;
  pwmb = Pico32xMem->pwm;

  if (stereo)
  {
    if (xmd == 0x05) {
      // normal
      while (length-- > 0) {
        *buf32++ += pwmb[0];
        *buf32++ += pwmb[1];

        p += step;
        pwmb += (p >> 16) * 2;
        p &= 0xffff;
      }
    }
    else if (xmd == 0x0a) {
      // channel swap
      while (length-- > 0) {
        *buf32++ += pwmb[1];
        *buf32++ += pwmb[0];

        p += step;
        pwmb += (p >> 16) * 2;
        p &= 0xffff;
      }
    }
    else {
      // mono - LMD, RMD specify dst
      if (xmd & 0x06) // src is R
        pwmb++;
      if (xmd & 0x0c) // dst is R
        buf32++;
      while (length-- > 0) {
        *buf32 += *pwmb;

        p += step;
        pwmb += (p >> 16) * 2;
        p &= 0xffff;
        buf32 += 2;
      }
    }
  }
  else
  {
    // mostly unused
    while (length-- > 0) {
      *buf32++ += pwmb[0];

      p += step;
      pwmb += (p >> 16) * 2;
      p &= 0xffff;
    }
  }

  elprintf(EL_PWM, "pwm_update: pwm_ptr %d, len %d, step %04x, done %d",
    pwm_ptr, length, step, (pwmb - Pico32xMem->pwm) / 2);

out:
  pwm_ptr = 0;
  pwm_silent = Pico32xMem->pwm_current[0] == 0
    && Pico32xMem->pwm_current[1] == 0;
}