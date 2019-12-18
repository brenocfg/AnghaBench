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
typedef  int u8 ;
typedef  unsigned int u32 ;
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_SMBCSR ; 
 int /*<<< orphan*/  JME_SMBINTF ; 
 int JME_SMB_BUSY_TIMEOUT ; 
 unsigned int SMBCSR_BUSY ; 
 unsigned int SMBINTF_HWADDR ; 
 unsigned int SMBINTF_HWADDR_SHIFT ; 
 unsigned int SMBINTF_HWCMD ; 
 unsigned int SMBINTF_HWDATR ; 
 unsigned int SMBINTF_HWDATR_SHIFT ; 
 unsigned int SMBINTF_HWRWN_READ ; 
 unsigned int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_hw (struct jme_adapter*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u8
jme_smb_read(struct jme_adapter *jme, unsigned int addr)
{
	u32 val;
	int to;

	val = jread32(jme, JME_SMBCSR);
	to = JME_SMB_BUSY_TIMEOUT;
	while ((val & SMBCSR_BUSY) && --to) {
		msleep(1);
		val = jread32(jme, JME_SMBCSR);
	}
	if (!to) {
		msg_hw(jme, "SMB Bus Busy.\n");
		return 0xFF;
	}

	jwrite32(jme, JME_SMBINTF,
		((addr << SMBINTF_HWADDR_SHIFT) & SMBINTF_HWADDR) |
		SMBINTF_HWRWN_READ |
		SMBINTF_HWCMD);

	val = jread32(jme, JME_SMBINTF);
	to = JME_SMB_BUSY_TIMEOUT;
	while ((val & SMBINTF_HWCMD) && --to) {
		msleep(1);
		val = jread32(jme, JME_SMBINTF);
	}
	if (!to) {
		msg_hw(jme, "SMB Bus Busy.\n");
		return 0xFF;
	}

	return (val & SMBINTF_HWDATR) >> SMBINTF_HWDATR_SHIFT;
}