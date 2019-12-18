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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  set_ar_dr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ksl_tl (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ksl_wave_fb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mul (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sl_rr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_instrument(UINT32 chan, UINT32 slot, UINT8* inst )
{
  set_mul(slot, inst[0]);
  set_mul(slot+1, inst[1]);
  set_ksl_tl(chan, inst[2]);
  set_ksl_wave_fb(chan, inst[3]);
  set_ar_dr(slot,   inst[4]);
  set_ar_dr(slot+1, inst[5]);
  set_sl_rr(slot,   inst[6]);
  set_sl_rr(slot+1, inst[7]);
}