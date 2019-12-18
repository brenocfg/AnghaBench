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
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ee_flsh_adapter ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t nes_store_adapter(struct device_driver *ddp,
	const char *buf, size_t count)
{
	char *p = (char *)buf;

	ee_flsh_adapter = simple_strtoul(p, &p, 10);
	return strnlen(buf, count);
}