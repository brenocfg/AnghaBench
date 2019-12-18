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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int cx18_av_read (struct cx18*,int) ; 

__attribute__((used)) static int get_balance(struct cx18 *cx)
{
	/* balance is 7 bit, 0 to -96dB */

	/* check PATH1_BAL_LEVEL */
	int balance = cx18_av_read(cx, 0x8d5) & 0x7f;
	/* check PATH1_BAL_LEFT */
	if ((cx18_av_read(cx, 0x8d5) & 0x80) == 0)
		balance = 0x80 - balance;
	else
		balance = 0x80 + balance;
	return balance << 8;
}