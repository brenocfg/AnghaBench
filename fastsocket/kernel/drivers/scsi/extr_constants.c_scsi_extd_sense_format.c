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
struct TYPE_4__ {char const* text; unsigned short code12; } ;
struct TYPE_3__ {char const* fmt; unsigned char code1; unsigned char code2_min; unsigned char code2_max; } ;

/* Variables and functions */
 TYPE_2__* additional ; 
 TYPE_1__* additional2 ; 

const char *
scsi_extd_sense_format(unsigned char asc, unsigned char ascq) {
#ifdef CONFIG_SCSI_CONSTANTS
	int i;
	unsigned short code = ((asc << 8) | ascq);

	for (i = 0; additional[i].text; i++)
		if (additional[i].code12 == code)
			return additional[i].text;
	for (i = 0; additional2[i].fmt; i++) {
		if (additional2[i].code1 == asc &&
		    ascq >= additional2[i].code2_min &&
		    ascq <= additional2[i].code2_max)
			return additional2[i].fmt;
	}
#endif
	return NULL;
}