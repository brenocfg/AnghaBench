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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int auxd; int /*<<< orphan*/  isac; int /*<<< orphan*/  auxa; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  byteout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  insb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
NETjet_ReadICfifo(struct IsdnCardState *cs, u_char *data, int size)
{
	cs->hw.njet.auxd &= 0xfc;
	byteout(cs->hw.njet.auxa, cs->hw.njet.auxd);
	insb(cs->hw.njet.isac, data, size);
}