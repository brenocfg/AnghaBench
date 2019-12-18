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
struct stlport {int uartaddr; scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ XP_ADDR ; 
 scalar_t__ XP_DATA ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void stl_sc26198setreg(struct stlport *portp, int regnr, int value)
{
	outb((regnr | portp->uartaddr), (portp->ioaddr + XP_ADDR));
	outb(value, (portp->ioaddr + XP_DATA));
}