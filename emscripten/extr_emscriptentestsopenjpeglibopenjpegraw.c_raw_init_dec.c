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
struct TYPE_3__ {unsigned char* start; int lenmax; scalar_t__ ct; scalar_t__ c; scalar_t__ len; } ;
typedef  TYPE_1__ opj_raw_t ;

/* Variables and functions */

void raw_init_dec(opj_raw_t *raw, unsigned char *bp, int len) {
	raw->start = bp;
	raw->lenmax = len;
	raw->len = 0;
	raw->c = 0;
	raw->ct = 0;
}