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
 int /*<<< orphan*/  cio_byteout (int /*<<< orphan*/ *,unsigned char) ; 

unsigned int cio_write(opj_cio_t *cio, unsigned int v, int n) {
	int i;
	for (i = n - 1; i >= 0; i--) {
		if( !cio_byteout(cio, (unsigned char) ((v >> (i << 3)) & 0xff)) )
			return 0;
	}
	return n;
}