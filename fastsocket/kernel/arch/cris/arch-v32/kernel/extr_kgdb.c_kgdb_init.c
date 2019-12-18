#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ser0; int ser1; int ser2; int ser3; void* dav; } ;
typedef  TYPE_1__ reg_ser_rw_intr_mask ;
typedef  TYPE_1__ reg_intr_vect_rw_mask ;

/* Variables and functions */
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  SER0_INTR_VECT ; 
 int /*<<< orphan*/  SER1_INTR_VECT ; 
 int /*<<< orphan*/  SER2_INTR_VECT ; 
 int /*<<< orphan*/  SER3_INTR_VECT ; 
 int /*<<< orphan*/  intr_vect ; 
 int /*<<< orphan*/  kgdb_handle_exception ; 
 int /*<<< orphan*/  regi_irq ; 
 int /*<<< orphan*/  regi_ser0 ; 
 int /*<<< orphan*/  regi_ser1 ; 
 int /*<<< orphan*/  regi_ser2 ; 
 int /*<<< orphan*/  regi_ser3 ; 
 void* regk_ser_yes ; 
 int /*<<< orphan*/  rw_intr_mask ; 
 int /*<<< orphan*/  rw_mask ; 
 int /*<<< orphan*/  ser ; 
 int /*<<< orphan*/  set_exception_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kgdb_init(void)
{
	reg_intr_vect_rw_mask intr_mask;
	reg_ser_rw_intr_mask ser_intr_mask;

	/* Configure the kgdb serial port. */
#if defined(CONFIG_ETRAX_KGDB_PORT0)
	/* Note: no shortcut registered (not handled by multiple_interrupt).
	   See entry.S.  */
	set_exception_vector(SER0_INTR_VECT, kgdb_handle_exception);
	/* Enable the ser irq in the global config. */
	intr_mask = REG_RD(intr_vect, regi_irq, rw_mask);
	intr_mask.ser0 = 1;
	REG_WR(intr_vect, regi_irq, rw_mask, intr_mask);

	ser_intr_mask = REG_RD(ser, regi_ser0, rw_intr_mask);
	ser_intr_mask.dav = regk_ser_yes;
	REG_WR(ser, regi_ser0, rw_intr_mask, ser_intr_mask);
#elif defined(CONFIG_ETRAX_KGDB_PORT1)
	/* Note: no shortcut registered (not handled by multiple_interrupt).
	   See entry.S.  */
	set_exception_vector(SER1_INTR_VECT, kgdb_handle_exception);
	/* Enable the ser irq in the global config. */
	intr_mask = REG_RD(intr_vect, regi_irq, rw_mask);
	intr_mask.ser1 = 1;
	REG_WR(intr_vect, regi_irq, rw_mask, intr_mask);

	ser_intr_mask = REG_RD(ser, regi_ser1, rw_intr_mask);
	ser_intr_mask.dav = regk_ser_yes;
	REG_WR(ser, regi_ser1, rw_intr_mask, ser_intr_mask);
#elif defined(CONFIG_ETRAX_KGDB_PORT2)
	/* Note: no shortcut registered (not handled by multiple_interrupt).
	   See entry.S.  */
	set_exception_vector(SER2_INTR_VECT, kgdb_handle_exception);
	/* Enable the ser irq in the global config. */
	intr_mask = REG_RD(intr_vect, regi_irq, rw_mask);
	intr_mask.ser2 = 1;
	REG_WR(intr_vect, regi_irq, rw_mask, intr_mask);

	ser_intr_mask = REG_RD(ser, regi_ser2, rw_intr_mask);
	ser_intr_mask.dav = regk_ser_yes;
	REG_WR(ser, regi_ser2, rw_intr_mask, ser_intr_mask);
#elif defined(CONFIG_ETRAX_KGDB_PORT3)
	/* Note: no shortcut registered (not handled by multiple_interrupt).
	   See entry.S.  */
	set_exception_vector(SER3_INTR_VECT, kgdb_handle_exception);
	/* Enable the ser irq in the global config. */
	intr_mask = REG_RD(intr_vect, regi_irq, rw_mask);
	intr_mask.ser3 = 1;
	REG_WR(intr_vect, regi_irq, rw_mask, intr_mask);

	ser_intr_mask = REG_RD(ser, regi_ser3, rw_intr_mask);
	ser_intr_mask.dav = regk_ser_yes;
	REG_WR(ser, regi_ser3, rw_intr_mask, ser_intr_mask);
#endif

}