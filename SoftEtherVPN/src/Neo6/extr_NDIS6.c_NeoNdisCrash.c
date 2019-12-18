#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ NEO_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  NeoCopy (int /*<<< orphan*/ ,char*,int) ; 

void NeoNdisCrash()
{
	NEO_QUEUE *q;
	q = (NEO_QUEUE *)0xACACACAC;
	q->Size = 128;
	NeoCopy(q->Buf, "ABCDEFG", 8);
}