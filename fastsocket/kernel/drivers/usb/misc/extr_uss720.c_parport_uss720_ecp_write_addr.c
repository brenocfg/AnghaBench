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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECR_ECP ; 
 int /*<<< orphan*/  ECR_PS2 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ change_mode (struct parport*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_1284_register (struct parport*,int,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t parport_uss720_ecp_write_addr(struct parport *pp, const void *buffer, size_t len, int flags)
{
	size_t written = 0;

	if (change_mode(pp, ECR_ECP))
		return 0;
	for (; written < len; written++) {
		if (set_1284_register(pp, 5, *(char *)buffer, GFP_KERNEL))
			break;
		buffer++;
	}
	change_mode(pp, ECR_PS2);
	return written;
}