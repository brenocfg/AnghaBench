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
 int /*<<< orphan*/  inportb (int) ; 
 int /*<<< orphan*/  outportb (int,int) ; 

void SetBorder(void)
{
 inportb(0x3da);
 outportb(0x3c0,(0x11|0x20));
 outportb(0x3c0,0x80);
}