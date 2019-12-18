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
 int /*<<< orphan*/  ASCEBC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBC_TOUPPER (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_CMDLEN ; 
 int /*<<< orphan*/  VMWDT_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __diag288 (unsigned int,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmwdt_cmd ; 
 scalar_t__ vmwdt_conceal ; 
 int /*<<< orphan*/  vmwdt_interval ; 
 int /*<<< orphan*/  vmwdt_is_open ; 
 unsigned int wdt_conceal ; 
 unsigned int wdt_init ; 

__attribute__((used)) static int vmwdt_keepalive(void)
{
	/* we allocate new memory every time to avoid having
	 * to track the state. static allocation is not an
	 * option since that might not be contiguous in real
	 * storage in case of a modular build */
	static char *ebc_cmd;
	size_t len;
	int ret;
	unsigned int func;

	ebc_cmd = kmalloc(MAX_CMDLEN, GFP_KERNEL);
	if (!ebc_cmd)
		return -ENOMEM;

	len = strlcpy(ebc_cmd, vmwdt_cmd, MAX_CMDLEN);
	ASCEBC(ebc_cmd, MAX_CMDLEN);
	EBC_TOUPPER(ebc_cmd, MAX_CMDLEN);

	func = vmwdt_conceal ? (wdt_init | wdt_conceal) : wdt_init;
	set_bit(VMWDT_RUNNING, &vmwdt_is_open);
	ret = __diag288(func, vmwdt_interval, ebc_cmd, len);
	WARN_ON(ret != 0);
	kfree(ebc_cmd);
	return ret;
}