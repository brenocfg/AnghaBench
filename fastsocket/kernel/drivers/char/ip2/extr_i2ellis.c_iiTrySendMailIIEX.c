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
struct TYPE_3__ {int /*<<< orphan*/  i2eXMail; int /*<<< orphan*/  i2eStatus; } ;

/* Variables and functions */
 int STE_OUT_MAIL ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iiTrySendMailIIEX(i2eBordStrPtr pB, unsigned char mail)
{
	if (inb(pB->i2eStatus) & STE_OUT_MAIL)
		return 0;
	outb(mail, pB->i2eXMail);
	return 1;
}