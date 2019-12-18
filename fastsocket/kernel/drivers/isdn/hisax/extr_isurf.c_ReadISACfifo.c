#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  isac; } ;
struct TYPE_4__ {TYPE_1__ isurf; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ReadISACfifo(struct IsdnCardState *cs, u_char * data, int size)
{
	register int i;
	for (i = 0; i < size; i++)
		data[i] = readb(cs->hw.isurf.isac);
}