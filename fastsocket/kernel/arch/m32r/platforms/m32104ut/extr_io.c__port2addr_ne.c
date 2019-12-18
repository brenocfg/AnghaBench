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
 scalar_t__ NONCACHE_OFFSET ; 

__attribute__((used)) static inline void *_port2addr_ne(unsigned long port)
{
	return (void *)(port + NONCACHE_OFFSET + 0x01000000);
}