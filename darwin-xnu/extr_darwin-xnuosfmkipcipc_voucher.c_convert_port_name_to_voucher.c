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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  IV_NULL ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_port_to_voucher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_space () ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_translate_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ipc_voucher_t
convert_port_name_to_voucher(
	mach_port_name_t	voucher_name)
{
	ipc_voucher_t iv;
	kern_return_t kr;
	ipc_port_t port;

	if (MACH_PORT_VALID(voucher_name)) {
		kr = ipc_port_translate_send(current_space(), voucher_name, &port);
		if (KERN_SUCCESS != kr)
			return IV_NULL;

		iv = convert_port_to_voucher(port);
		ip_unlock(port);
		return iv;
	}
	return IV_NULL;
}