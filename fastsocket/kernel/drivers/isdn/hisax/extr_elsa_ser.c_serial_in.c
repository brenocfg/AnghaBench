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
typedef  unsigned int u_int ;
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ModemIn ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static inline unsigned int serial_in(struct IsdnCardState *cs, int offset)
{
#ifdef SERIAL_DEBUG_REG
	u_int val = inb(cs->hw.elsa.base + 8 + offset);
	debugl1(cs,"in   %s %02x",ModemIn[offset], val);
	return(val);
#else
	return inb(cs->hw.elsa.base + 8 + offset);
#endif
}