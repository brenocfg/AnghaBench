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
 scalar_t__ EISA_bus ; 
 int /*<<< orphan*/  eisa_permute (unsigned short) ; 
 int /*<<< orphan*/  gsc_readw (int /*<<< orphan*/ ) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 

unsigned short eisa_in16(unsigned short port)
{
	if (EISA_bus)
		return le16_to_cpu(gsc_readw(eisa_permute(port)));
	return 0xffff;
}