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
struct TYPE_2__ {scalar_t__ kind; int data1; unsigned char data2; } ;

/* Variables and functions */
 scalar_t__ KIND_END ; 
 TYPE_1__* ati_remote_tbl ; 

__attribute__((used)) static int ati_remote_event_lookup(int rem, unsigned char d1, unsigned char d2)
{
	int i;

	for (i = 0; ati_remote_tbl[i].kind != KIND_END; i++) {
		/*
		 * Decide if the table entry matches the remote input.
		 */
		if ((((ati_remote_tbl[i].data1 & 0x0f) == (d1 & 0x0f))) &&
		    ((((ati_remote_tbl[i].data1 >> 4) -
		       (d1 >> 4) + rem) & 0x0f) == 0x0f) &&
		    (ati_remote_tbl[i].data2 == d2))
			return i;

	}
	return -1;
}