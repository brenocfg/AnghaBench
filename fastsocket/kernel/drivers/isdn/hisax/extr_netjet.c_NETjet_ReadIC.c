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
typedef  int u_char ;
struct TYPE_4__ {int auxd; scalar_t__ isac; int /*<<< orphan*/  auxa; } ;
struct TYPE_3__ {TYPE_2__ njet; } ;
struct IsdnCardState {TYPE_1__ hw; } ;

/* Variables and functions */
 int bytein (scalar_t__) ; 
 int /*<<< orphan*/  byteout (int /*<<< orphan*/ ,int) ; 

u_char
NETjet_ReadIC(struct IsdnCardState *cs, u_char offset)
{
	u_char ret;
	
	cs->hw.njet.auxd &= 0xfc;
	cs->hw.njet.auxd |= (offset>>4) & 3;
	byteout(cs->hw.njet.auxa, cs->hw.njet.auxd);
	ret = bytein(cs->hw.njet.isac + ((offset & 0xf)<<2));
	return(ret);
}