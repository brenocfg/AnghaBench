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
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ModemOut ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static inline void serial_outp(struct IsdnCardState *cs, int offset,
			       int value)
{
#ifdef SERIAL_DEBUG_REG
#ifdef ELSA_SERIAL_NOPAUSE_IO
	debugl1(cs,"outp %s %02x",ModemOut[offset], value);
#else
	debugl1(cs,"outP %s %02x",ModemOut[offset], value);
#endif
#endif
#ifdef ELSA_SERIAL_NOPAUSE_IO
	outb(value, cs->hw.elsa.base + 8 + offset);
#else
    	outb_p(value, cs->hw.elsa.base + 8 + offset);
#endif
}