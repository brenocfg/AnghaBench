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
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  l1m; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ *,unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAC_CIR0 ; 
 unsigned char ISAC_CIR0_CIC0 ; 
 unsigned char ISAC_CIR0_CIC1 ; 
 int /*<<< orphan*/  ISAC_CIR1 ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 unsigned char stub2 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isac_cisq_interrupt(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISAC_CIR0);
	DBG(DBG_IRQ, "CIR0 %#x", val);
	if (val & ISAC_CIR0_CIC0) {
		DBG(DBG_IRQ, "CODR0 %#x", (val >> 2) & 0xf);
		FsmEvent(&isac->l1m, (val >> 2) & 0xf, NULL);
	}
	if (val & ISAC_CIR0_CIC1) {
		val = isac->read_isac(isac, ISAC_CIR1);
		DBG(DBG_WARN, "ISAC CIR1 %#x", val );
	}
}