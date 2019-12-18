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
typedef  int /*<<< orphan*/  u8 ;
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_AFTER_PNP ; 
 int /*<<< orphan*/  CR_CWMIN_CWMAX ; 
 int /*<<< orphan*/  CR_GPI_EN ; 
 int CWIN_SIZE ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int disable_hwint (struct zd_chip*) ; 
 int /*<<< orphan*/  dump_fw_registers (struct zd_chip*) ; 
 int hw_init (struct zd_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int print_fw_version (struct zd_chip*) ; 
 int /*<<< orphan*/  print_id (struct zd_chip*) ; 
 int read_cal_int_tables (struct zd_chip*) ; 
 int read_fw_regs_offset (struct zd_chip*) ; 
 int read_pod (struct zd_chip*,int /*<<< orphan*/ *) ; 
 int set_mandatory_rates (struct zd_chip*,int) ; 
 int test_init (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_iowrite32_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 
 int zd_rf_init_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int zd_chip_init_hw(struct zd_chip *chip)
{
	int r;
	u8 rf_type;

	dev_dbg_f(zd_chip_dev(chip), "\n");

	mutex_lock(&chip->mutex);

#ifdef DEBUG
	r = test_init(chip);
	if (r)
		goto out;
#endif
	r = zd_iowrite32_locked(chip, 1, CR_AFTER_PNP);
	if (r)
		goto out;

	r = read_fw_regs_offset(chip);
	if (r)
		goto out;

	/* GPI is always disabled, also in the other driver.
	 */
	r = zd_iowrite32_locked(chip, 0, CR_GPI_EN);
	if (r)
		goto out;
	r = zd_iowrite32_locked(chip, CWIN_SIZE, CR_CWMIN_CWMAX);
	if (r)
		goto out;
	/* Currently we support IEEE 802.11g for full and high speed USB.
	 * It might be discussed, whether we should suppport pure b mode for
	 * full speed USB.
	 */
	r = set_mandatory_rates(chip, 1);
	if (r)
		goto out;
	/* Disabling interrupts is certainly a smart thing here.
	 */
	r = disable_hwint(chip);
	if (r)
		goto out;
	r = read_pod(chip, &rf_type);
	if (r)
		goto out;
	r = hw_init(chip);
	if (r)
		goto out;
	r = zd_rf_init_hw(&chip->rf, rf_type);
	if (r)
		goto out;

	r = print_fw_version(chip);
	if (r)
		goto out;

#ifdef DEBUG
	dump_fw_registers(chip);
	r = test_init(chip);
	if (r)
		goto out;
#endif /* DEBUG */

	r = read_cal_int_tables(chip);
	if (r)
		goto out;

	print_id(chip);
out:
	mutex_unlock(&chip->mutex);
	return r;
}