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
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 unsigned char cio_read (int /*<<< orphan*/ *,int) ; 

unsigned int jpt_read_VBAS_info(opj_cio_t *cio, unsigned int value) {
	unsigned char elmt;

	elmt = cio_read(cio, 1);
	while ((elmt >> 7) == 1) {
		value = (value << 7);
		value |= (elmt & 0x7f);
		elmt = cio_read(cio, 1);
	}
	value = (value << 7);
	value |= (elmt & 0x7f);

	return value;
}