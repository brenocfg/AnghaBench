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
struct bna_ethport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_ethport_stop_cbfn (struct bna_ethport*) ; 

__attribute__((used)) static void
bna_ethport_sm_stopped_entry(struct bna_ethport *ethport)
{
	call_ethport_stop_cbfn(ethport);
}