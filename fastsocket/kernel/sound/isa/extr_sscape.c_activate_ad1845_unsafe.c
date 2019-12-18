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
 int /*<<< orphan*/  GA_CDCFG_REG ; 
 int /*<<< orphan*/  GA_HMCTL_REG ; 
 int sscape_read_unsafe (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscape_write_unsafe (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void activate_ad1845_unsafe(unsigned io_base)
{
	sscape_write_unsafe(io_base, GA_HMCTL_REG, (sscape_read_unsafe(io_base, GA_HMCTL_REG) & 0xcf) | 0x10);
	sscape_write_unsafe(io_base, GA_CDCFG_REG, 0x80);
}