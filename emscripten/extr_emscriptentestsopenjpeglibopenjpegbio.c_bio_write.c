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
typedef  int /*<<< orphan*/  opj_bio_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_putbit (int /*<<< orphan*/ *,int) ; 

void bio_write(opj_bio_t *bio, int v, int n) {
	int i;
	for (i = n - 1; i >= 0; i--) {
		bio_putbit(bio, (v >> i) & 1);
	}
}