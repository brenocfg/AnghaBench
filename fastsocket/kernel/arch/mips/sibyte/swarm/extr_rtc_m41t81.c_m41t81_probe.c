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
 int /*<<< orphan*/  M41T81REG_SC ; 
 int m41t81_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m41t81_write (int /*<<< orphan*/ ,unsigned int) ; 

int m41t81_probe(void)
{
	unsigned int tmp;

	/* enable chip if it is not enabled yet */
	tmp = m41t81_read(M41T81REG_SC);
	m41t81_write(M41T81REG_SC, tmp & 0x7f);

	return (m41t81_read(M41T81REG_SC) != -1);
}