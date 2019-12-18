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
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__* firsts; scalar_t__* counts; } ;
typedef  TYPE_1__ scsi_changer ;

/* Variables and functions */
 int CH_TYPES ; 

__attribute__((used)) static int
ch_elem_to_typecode(scsi_changer *ch, u_int elem)
{
	int i;

	for (i = 0; i < CH_TYPES; i++) {
		if (elem >= ch->firsts[i]  &&
		    elem <  ch->firsts[i] +
	            ch->counts[i])
			return i+1;
	}
	return 0;
}