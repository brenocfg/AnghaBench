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

/* Variables and functions */
 int /*<<< orphan*/  CCDC_ALAW ; 
 int /*<<< orphan*/  CCDC_BLKCMP ; 
 int /*<<< orphan*/  CCDC_CLAMP ; 
 int /*<<< orphan*/  CCDC_COLPTN ; 
 int /*<<< orphan*/  CCDC_DCSUB ; 
 int /*<<< orphan*/  CCDC_FMTCFG ; 
 int /*<<< orphan*/  CCDC_FMT_HORZ ; 
 int /*<<< orphan*/  CCDC_FMT_VERT ; 
 int /*<<< orphan*/  CCDC_FPC ; 
 int /*<<< orphan*/  CCDC_FPC_ADDR ; 
 int /*<<< orphan*/  CCDC_HORZ_INFO ; 
 int /*<<< orphan*/  CCDC_HSIZE_OFF ; 
 int /*<<< orphan*/  CCDC_SDOFST ; 
 int /*<<< orphan*/  CCDC_SYN_MODE ; 
 int /*<<< orphan*/  CCDC_VERT_LINES ; 
 int /*<<< orphan*/  CCDC_VERT_START ; 
 int /*<<< orphan*/  CCDC_VP_OUT ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int regr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_readregs(void)
{
	unsigned int val = 0;

	val = regr(CCDC_ALAW);
	dev_notice(dev, "\nReading 0x%x to ALAW...\n", val);
	val = regr(CCDC_CLAMP);
	dev_notice(dev, "\nReading 0x%x to CLAMP...\n", val);
	val = regr(CCDC_DCSUB);
	dev_notice(dev, "\nReading 0x%x to DCSUB...\n", val);
	val = regr(CCDC_BLKCMP);
	dev_notice(dev, "\nReading 0x%x to BLKCMP...\n", val);
	val = regr(CCDC_FPC_ADDR);
	dev_notice(dev, "\nReading 0x%x to FPC_ADDR...\n", val);
	val = regr(CCDC_FPC);
	dev_notice(dev, "\nReading 0x%x to FPC...\n", val);
	val = regr(CCDC_FMTCFG);
	dev_notice(dev, "\nReading 0x%x to FMTCFG...\n", val);
	val = regr(CCDC_COLPTN);
	dev_notice(dev, "\nReading 0x%x to COLPTN...\n", val);
	val = regr(CCDC_FMT_HORZ);
	dev_notice(dev, "\nReading 0x%x to FMT_HORZ...\n", val);
	val = regr(CCDC_FMT_VERT);
	dev_notice(dev, "\nReading 0x%x to FMT_VERT...\n", val);
	val = regr(CCDC_HSIZE_OFF);
	dev_notice(dev, "\nReading 0x%x to HSIZE_OFF...\n", val);
	val = regr(CCDC_SDOFST);
	dev_notice(dev, "\nReading 0x%x to SDOFST...\n", val);
	val = regr(CCDC_VP_OUT);
	dev_notice(dev, "\nReading 0x%x to VP_OUT...\n", val);
	val = regr(CCDC_SYN_MODE);
	dev_notice(dev, "\nReading 0x%x to SYN_MODE...\n", val);
	val = regr(CCDC_HORZ_INFO);
	dev_notice(dev, "\nReading 0x%x to HORZ_INFO...\n", val);
	val = regr(CCDC_VERT_START);
	dev_notice(dev, "\nReading 0x%x to VERT_START...\n", val);
	val = regr(CCDC_VERT_LINES);
	dev_notice(dev, "\nReading 0x%x to VERT_LINES...\n", val);
}