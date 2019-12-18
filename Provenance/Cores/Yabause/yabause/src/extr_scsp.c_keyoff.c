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
struct Slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RELEASE ; 
 int /*<<< orphan*/  change_envelope_state (struct Slot*,int /*<<< orphan*/ ) ; 

void keyoff(struct Slot * slot)
{
   change_envelope_state(slot, RELEASE);
}