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
struct TYPE_3__ {int /*<<< orphan*/  i2eData; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iiWriteWord8(i2eBordStrPtr pB, unsigned short value)
{
	outb((char)value, pB->i2eData);
	outb((char)(value >> 8), pB->i2eData);
}