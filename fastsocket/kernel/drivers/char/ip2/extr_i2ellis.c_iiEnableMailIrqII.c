#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_3__ {int /*<<< orphan*/  i2ePointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEL_MASK ; 
 int /*<<< orphan*/  ST_IN_MAIL ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iiEnableMailIrqII(i2eBordStrPtr pB)
{
	outb(SEL_MASK, pB->i2ePointer);
	outb(ST_IN_MAIL, pB->i2ePointer);
}