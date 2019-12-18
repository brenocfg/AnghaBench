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
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char const*,int,int,int,void const*,size_t,int) ; 

void print_hex_dump_bytes(const char *prefix_str, int prefix_type,
			const void *buf, size_t len)
{
	print_hex_dump(KERN_DEBUG, prefix_str, prefix_type, 16, 1,
			buf, len, 1);
}