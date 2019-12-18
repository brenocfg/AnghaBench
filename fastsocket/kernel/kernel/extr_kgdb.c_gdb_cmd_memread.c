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
struct kgdb_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  error_packet (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kgdb_hex2long (char**,unsigned long*) ; 
 int kgdb_mem2hex (char*,int /*<<< orphan*/ ,unsigned long) ; 
 char* remcom_in_buffer ; 
 int /*<<< orphan*/  remcom_out_buffer ; 

__attribute__((used)) static void gdb_cmd_memread(struct kgdb_state *ks)
{
	char *ptr = &remcom_in_buffer[1];
	unsigned long length;
	unsigned long addr;
	int err;

	if (kgdb_hex2long(&ptr, &addr) > 0 && *ptr++ == ',' &&
					kgdb_hex2long(&ptr, &length) > 0) {
		err = kgdb_mem2hex((char *)addr, remcom_out_buffer, length);
		if (err)
			error_packet(remcom_out_buffer, err);
	} else {
		error_packet(remcom_out_buffer, -EINVAL);
	}
}