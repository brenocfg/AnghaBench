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
struct TYPE_3__ {scalar_t__ isac; } ;
struct TYPE_4__ {TYPE_1__ njet; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int AMD_CR ; 
 int AMD_DR ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static unsigned char
ReadByteAmd7930(struct IsdnCardState *cs, unsigned char offset)
{
	/* direct register */
	if(offset < 8)
		return (inb(cs->hw.njet.isac + 4*offset));

	/* indirect register */
	else {
		outb(offset, cs->hw.njet.isac + 4*AMD_CR);
		return(inb(cs->hw.njet.isac + 4*AMD_DR));
	}
}