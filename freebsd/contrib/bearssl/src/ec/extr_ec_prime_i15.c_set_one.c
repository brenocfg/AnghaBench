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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
set_one(uint16_t *x, const uint16_t *p)
{
	size_t plen;

	plen = (p[0] + 31) >> 4;
	memset(x, 0, plen * sizeof *x);
	x[0] = p[0];
	x[1] = 0x0001;
}