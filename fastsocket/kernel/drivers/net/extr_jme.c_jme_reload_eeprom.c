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
typedef  int u32 ;
struct jme_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EIO ; 
 int JME_EEPROM_RELOAD_TIMEOUT ; 
 int /*<<< orphan*/  JME_SMBCSR ; 
 int SMBCSR_CNACK ; 
 int SMBCSR_EEPROMD ; 
 int SMBCSR_RELOAD ; 
 int /*<<< orphan*/  jeprintk (int /*<<< orphan*/ ,char*) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int
jme_reload_eeprom(struct jme_adapter *jme)
{
	u32 val;
	int i;

	val = jread32(jme, JME_SMBCSR);

	if (val & SMBCSR_EEPROMD) {
		val |= SMBCSR_CNACK;
		jwrite32(jme, JME_SMBCSR, val);
		val |= SMBCSR_RELOAD;
		jwrite32(jme, JME_SMBCSR, val);
		mdelay(12);

		for (i = JME_EEPROM_RELOAD_TIMEOUT; i > 0; --i) {
			mdelay(1);
			if ((jread32(jme, JME_SMBCSR) & SMBCSR_RELOAD) == 0)
				break;
		}

		if (i == 0) {
			jeprintk(jme->pdev, "eeprom reload timeout\n");
			return -EIO;
		}
	}

	return 0;
}