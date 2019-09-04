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
 unsigned short* __seed48 ; 
 int /*<<< orphan*/  memcpy (unsigned short*,unsigned short*,int) ; 

unsigned short *seed48(unsigned short *s)
{
	static unsigned short p[3];
	memcpy(p, __seed48, sizeof p);
	memcpy(__seed48, s, sizeof p);
	return p;
}