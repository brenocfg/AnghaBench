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
struct hvsi_struct {int state; int /*<<< orphan*/  stateq; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_state (struct hvsi_struct*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __set_state(struct hvsi_struct *hp, int state)
{
	hp->state = state;
	print_state(hp);
	wake_up_all(&hp->stateq);
}