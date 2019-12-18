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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  __write_ports_addfd (char*) ; 
 int /*<<< orphan*/  __write_ports_addxprt (char*) ; 
 int /*<<< orphan*/  __write_ports_delfd (char*) ; 
 int /*<<< orphan*/  __write_ports_delxprt (char*) ; 
 int /*<<< orphan*/  __write_ports_names (char*) ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 

__attribute__((used)) static ssize_t __write_ports(struct file *file, char *buf, size_t size)
{
	if (size == 0)
		return __write_ports_names(buf);

	if (isdigit(buf[0]))
		return __write_ports_addfd(buf);

	if (buf[0] == '-' && isdigit(buf[1]))
		return __write_ports_delfd(buf);

	if (isalpha(buf[0]))
		return __write_ports_addxprt(buf);

	if (buf[0] == '-' && isalpha(buf[1]))
		return __write_ports_delxprt(buf);

	return -EINVAL;
}