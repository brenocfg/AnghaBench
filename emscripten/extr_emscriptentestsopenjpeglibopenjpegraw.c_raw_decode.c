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
struct TYPE_3__ {int ct; scalar_t__ len; scalar_t__ lenmax; int c; int* start; } ;
typedef  TYPE_1__ opj_raw_t ;

/* Variables and functions */

int raw_decode(opj_raw_t *raw) {
	int d;
	if (raw->ct == 0) {
		raw->ct = 8;
		if (raw->len == raw->lenmax) {
			raw->c = 0xff;
		} else {
			if (raw->c == 0xff) {
				raw->ct = 7;
			}
			raw->c = *(raw->start + raw->len);
			raw->len++;
		}
	}
	raw->ct--;
	d = (raw->c >> raw->ct) & 0x01;
	
	return d;
}