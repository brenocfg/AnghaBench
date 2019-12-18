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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  OPLL ;

/* Variables and functions */
 int calc (int /*<<< orphan*/ *) ; 

void OPLL_fillbuf(OPLL* opll, int32 *buf, int32 len, int shift) {
	while (len > 0) {
		*buf += (calc(opll) + 32768) << shift;
		buf++;
		len--;
	}
}