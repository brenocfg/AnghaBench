#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ct; } ;
typedef  TYPE_1__ opj_bio_t ;

/* Variables and functions */
 scalar_t__ bio_byteout (TYPE_1__*) ; 

int bio_flush(opj_bio_t *bio) {
	bio->ct = 0;
	if (bio_byteout(bio)) {
		return 1;
	}
	if (bio->ct == 7) {
		bio->ct = 0;
		if (bio_byteout(bio)) {
			return 1;
		}
	}
	return 0;
}