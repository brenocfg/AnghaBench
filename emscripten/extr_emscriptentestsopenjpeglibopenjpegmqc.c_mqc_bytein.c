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
struct TYPE_3__ {unsigned int* bp; unsigned int* end; int c; int ct; } ;
typedef  TYPE_1__ opj_mqc_t ;

/* Variables and functions */

__attribute__((used)) static void mqc_bytein(opj_mqc_t *const mqc) {
	if (mqc->bp != mqc->end) {
		unsigned int c;
		if (mqc->bp + 1 != mqc->end) {
			c = *(mqc->bp + 1);
		} else {
			c = 0xff;
		}
		if (*mqc->bp == 0xff) {
			if (c > 0x8f) {
				mqc->c += 0xff00;
				mqc->ct = 8;
			} else {
				mqc->bp++;
				mqc->c += c << 9;
				mqc->ct = 7;
			}
		} else {
			mqc->bp++;
			mqc->c += c << 8;
			mqc->ct = 8;
		}
	} else {
		mqc->c += 0xff00;
		mqc->ct = 8;
	}
}