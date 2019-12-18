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
struct TYPE_4__ {char* omsg; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
 int /*<<< orphan*/  isdnloop_fake (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
isdnloop_fake_err(isdnloop_card * card)
{
	char buf[60];

	sprintf(buf, "E%s", card->omsg);
	isdnloop_fake(card, buf, -1);
	isdnloop_fake(card, "NAK", -1);
}