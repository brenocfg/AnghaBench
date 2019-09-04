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
 int cio_bytein (int /*<<< orphan*/ *) ; 

unsigned int cio_read(opj_cio_t *cio, int n) {
	int i;
	unsigned int v;
	v = 0;
	for (i = n - 1; i >= 0; i--) {
		v += cio_bytein(cio) << (i << 3);
	}
	return v;
}