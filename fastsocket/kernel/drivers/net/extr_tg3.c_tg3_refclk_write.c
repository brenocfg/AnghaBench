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
typedef  int u64 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_CTL ; 
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_CTL_RESUME ; 
 int TG3_EAV_REF_CLCK_CTL_STOP ; 
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_LSB ; 
 int /*<<< orphan*/  TG3_EAV_REF_CLCK_MSB ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_refclk_write(struct tg3 *tp, u64 newval)
{
	tw32(TG3_EAV_REF_CLCK_CTL, TG3_EAV_REF_CLCK_CTL_STOP);
	tw32(TG3_EAV_REF_CLCK_LSB, newval & 0xffffffff);
	tw32(TG3_EAV_REF_CLCK_MSB, newval >> 32);
	tw32_f(TG3_EAV_REF_CLCK_CTL, TG3_EAV_REF_CLCK_CTL_RESUME);
}