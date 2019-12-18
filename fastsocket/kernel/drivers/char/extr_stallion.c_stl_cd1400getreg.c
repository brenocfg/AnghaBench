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
struct stlport {scalar_t__ ioaddr; scalar_t__ uartaddr; } ;

/* Variables and functions */
 scalar_t__ EREG_DATA ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int stl_cd1400getreg(struct stlport *portp, int regnr)
{
	outb((regnr + portp->uartaddr), portp->ioaddr);
	return inb(portp->ioaddr + EREG_DATA);
}