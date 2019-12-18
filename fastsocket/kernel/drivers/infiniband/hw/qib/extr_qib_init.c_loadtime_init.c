#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct qib_devdata {int revision; TYPE_1__ intrchk_timer; int /*<<< orphan*/  eep_lock; int /*<<< orphan*/  eep_st_lock; int /*<<< orphan*/  qib_diag_trans_lock; int /*<<< orphan*/  uctxt_lock; int /*<<< orphan*/  sendctrl_lock; int /*<<< orphan*/  pioavail_lock; int /*<<< orphan*/  boardversion; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int ENOSYS ; 
 int QIB_CHIP_SWVERSION ; 
 int QLOGIC_IB_R_EMULATOR_MASK ; 
 int QLOGIC_IB_R_SOFTWARE_MASK ; 
 int QLOGIC_IB_R_SOFTWARE_SHIFT ; 
 int init_pioavailregs (struct qib_devdata*) ; 
 int /*<<< orphan*/  init_shadow_tids (struct qib_devdata*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int,int,unsigned long long) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_get_eeprom_info (struct qib_devdata*) ; 
 scalar_t__ qib_mini_init ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_interrupt ; 

__attribute__((used)) static int loadtime_init(struct qib_devdata *dd)
{
	int ret = 0;

	if (((dd->revision >> QLOGIC_IB_R_SOFTWARE_SHIFT) &
	     QLOGIC_IB_R_SOFTWARE_MASK) != QIB_CHIP_SWVERSION) {
		qib_dev_err(dd,
			"Driver only handles version %d, chip swversion is %d (%llx), failng\n",
			QIB_CHIP_SWVERSION,
			(int)(dd->revision >>
				QLOGIC_IB_R_SOFTWARE_SHIFT) &
				QLOGIC_IB_R_SOFTWARE_MASK,
			(unsigned long long) dd->revision);
		ret = -ENOSYS;
		goto done;
	}

	if (dd->revision & QLOGIC_IB_R_EMULATOR_MASK)
		qib_devinfo(dd->pcidev, "%s", dd->boardversion);

	spin_lock_init(&dd->pioavail_lock);
	spin_lock_init(&dd->sendctrl_lock);
	spin_lock_init(&dd->uctxt_lock);
	spin_lock_init(&dd->qib_diag_trans_lock);
	spin_lock_init(&dd->eep_st_lock);
	mutex_init(&dd->eep_lock);

	if (qib_mini_init)
		goto done;

	ret = init_pioavailregs(dd);
	init_shadow_tids(dd);

	qib_get_eeprom_info(dd);

	/* setup time (don't start yet) to verify we got interrupt */
	init_timer(&dd->intrchk_timer);
	dd->intrchk_timer.function = verify_interrupt;
	dd->intrchk_timer.data = (unsigned long) dd;

done:
	return ret;
}