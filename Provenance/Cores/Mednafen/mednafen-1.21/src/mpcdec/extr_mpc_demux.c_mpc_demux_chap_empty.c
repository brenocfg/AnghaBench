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
struct TYPE_3__ {scalar_t__ chap_pos; scalar_t__ chap_nb; scalar_t__ chap; } ;
typedef  TYPE_1__ mpc_demux ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void mpc_demux_chap_empty(mpc_demux * d) {
	free(d->chap); d->chap = 0;
	d->chap_nb = 0; // -1 for undefined, 0 for no chapters
	d->chap_pos = 0;
}