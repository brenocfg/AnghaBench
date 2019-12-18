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
 unsigned long _inl (unsigned long) ; 
 int /*<<< orphan*/  delay () ; 

unsigned long _inl_p(unsigned long port)
{
	unsigned long v = _inl(port);
	delay();
	return (v);
}