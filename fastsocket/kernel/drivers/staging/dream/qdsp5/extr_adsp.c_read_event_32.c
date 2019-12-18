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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * read_event_addr ; 
 size_t read_event_size ; 

__attribute__((used)) static void read_event_32(void *buf, size_t len)
{
	uint32_t *dst = buf;
	uint32_t *src = read_event_addr;
	len /= 2;
	if (len > read_event_size)
		len = read_event_size;
	while (len--)
		*dst++ = *src++;
}