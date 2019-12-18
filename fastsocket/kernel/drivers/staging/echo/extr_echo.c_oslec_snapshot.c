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
struct oslec_state {int taps; int /*<<< orphan*/ * fir_taps16; int /*<<< orphan*/  snapshot; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void oslec_snapshot(struct oslec_state *ec)
{
	memcpy(ec->snapshot, ec->fir_taps16[0], ec->taps * sizeof(int16_t));
}