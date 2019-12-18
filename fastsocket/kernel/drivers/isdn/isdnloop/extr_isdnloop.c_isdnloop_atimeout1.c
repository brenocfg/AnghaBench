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
typedef  int /*<<< orphan*/  isdnloop_card ;

/* Variables and functions */
 int /*<<< orphan*/  isdnloop_atimeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
isdnloop_atimeout1(unsigned long data)
{
	isdnloop_card *card = (isdnloop_card *) data;
	isdnloop_atimeout(card, 1);
}