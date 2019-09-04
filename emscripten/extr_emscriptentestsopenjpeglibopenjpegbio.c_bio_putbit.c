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
struct TYPE_4__ {int ct; int buf; } ;
typedef  TYPE_1__ opj_bio_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_byteout (TYPE_1__*) ; 

__attribute__((used)) static void bio_putbit(opj_bio_t *bio, int b) {
	if (bio->ct == 0) {
		bio_byteout(bio);
	}
	bio->ct--;
	bio->buf |= b << bio->ct;
}