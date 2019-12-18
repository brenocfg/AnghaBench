#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pcibase; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  sb_intr (TYPE_1__*) ; 

__attribute__((used)) static void pci_intr(sb_devc *devc)
{
	int src = inb(devc->pcibase+0x1A);
	src&=3;
	if(src)
		sb_intr(devc);
}