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
struct dynpcc_info {int cur; int attempt; scalar_t__ cnt; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

__attribute__((used)) static void
jme_attempt_pcc(struct dynpcc_info *dpi, int atmp)
{
	if (likely(atmp == dpi->cur)) {
		dpi->cnt = 0;
		return;
	}

	if (dpi->attempt == atmp) {
		++(dpi->cnt);
	} else {
		dpi->attempt = atmp;
		dpi->cnt = 0;
	}

}