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
 int CMOS_READ (int) ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  PRINTK_1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRINTK_2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PRINTK_ERROR (char*) ; 
 int /*<<< orphan*/  TRACE_SMAPI ; 
 int g_usSmapiPort ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int smapi_init(void)
{
	int retval = -EIO;
	unsigned short usSmapiID = 0;
	unsigned long flags;

	PRINTK_1(TRACE_SMAPI, "smapi::smapi_init entry\n");

	spin_lock_irqsave(&rtc_lock, flags);
	usSmapiID = CMOS_READ(0x7C);
	usSmapiID |= (CMOS_READ(0x7D) << 8);
	spin_unlock_irqrestore(&rtc_lock, flags);
	PRINTK_2(TRACE_SMAPI, "smapi::smapi_init usSmapiID %x\n", usSmapiID);

	if (usSmapiID == 0x5349) {
		spin_lock_irqsave(&rtc_lock, flags);
		g_usSmapiPort = CMOS_READ(0x7E);
		g_usSmapiPort |= (CMOS_READ(0x7F) << 8);
		spin_unlock_irqrestore(&rtc_lock, flags);
		if (g_usSmapiPort == 0) {
			PRINTK_ERROR("smapi::smapi_init, ERROR unable to read from SMAPI port\n");
		} else {
			PRINTK_2(TRACE_SMAPI,
				"smapi::smapi_init, exit TRUE g_usSmapiPort %x\n",
				g_usSmapiPort);
			retval = 0;
			//SmapiQuerySystemID();
		}
	} else {
		PRINTK_ERROR("smapi::smapi_init, ERROR invalid usSmapiID\n");
		retval = -ENXIO;
	}

	return retval;
}