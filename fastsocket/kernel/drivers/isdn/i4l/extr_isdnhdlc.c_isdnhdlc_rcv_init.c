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
typedef  int u32 ;
struct isdnhdlc_vars {int do_adapt56; int do_bitreverse; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HDLC_56KBIT ; 
 int HDLC_BITREVERSE ; 
 int /*<<< orphan*/  HDLC_GET_DATA ; 
 int /*<<< orphan*/  memset (struct isdnhdlc_vars*,int /*<<< orphan*/ ,int) ; 

void isdnhdlc_rcv_init(struct isdnhdlc_vars *hdlc, u32 features)
{
	memset(hdlc, 0, sizeof(struct isdnhdlc_vars));
	hdlc->state = HDLC_GET_DATA;
	if (features & HDLC_56KBIT)
		hdlc->do_adapt56 = 1;
	if (features & HDLC_BITREVERSE)
		hdlc->do_bitreverse = 1;
}