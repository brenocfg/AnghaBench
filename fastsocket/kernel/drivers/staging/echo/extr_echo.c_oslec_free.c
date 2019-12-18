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
struct oslec_state {struct oslec_state* snapshot; struct oslec_state** fir_taps16; int /*<<< orphan*/  fir_state_bg; int /*<<< orphan*/  fir_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  fir16_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct oslec_state*) ; 

void oslec_free(struct oslec_state *ec)
{
	int i;

	fir16_free(&ec->fir_state);
	fir16_free(&ec->fir_state_bg);
	for (i = 0; i < 2; i++)
		kfree(ec->fir_taps16[i]);
	kfree(ec->snapshot);
	kfree(ec);
}