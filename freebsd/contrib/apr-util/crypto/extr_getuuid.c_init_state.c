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

/* Variables and functions */
 int /*<<< orphan*/  get_pseudo_node_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  true_random () ; 
 int /*<<< orphan*/  uuid_state_node ; 
 int /*<<< orphan*/  uuid_state_seqnum ; 

__attribute__((used)) static void init_state(void)
{
    uuid_state_seqnum = true_random();
    get_pseudo_node_identifier(uuid_state_node);
}