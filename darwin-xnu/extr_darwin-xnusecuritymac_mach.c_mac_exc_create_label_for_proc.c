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
struct proc {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct label*,struct proc*) ; 
 int /*<<< orphan*/  exc_action_label_populate ; 
 struct label* mac_exc_create_label () ; 

struct label *
mac_exc_create_label_for_proc(struct proc *proc)
{
	struct label *label = mac_exc_create_label();
	MAC_PERFORM(exc_action_label_populate, label, proc);
	return label;
}