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
 int /*<<< orphan*/  csr1212_release_keyval (scalar_t__) ; 
 int /*<<< orphan*/  csr_highlevel ; 
 int /*<<< orphan*/  hpsb_unregister_highlevel (int /*<<< orphan*/ *) ; 
 scalar_t__ node_cap ; 

void cleanup_csr(void)
{
	if (node_cap)
		csr1212_release_keyval(node_cap);
        hpsb_unregister_highlevel(&csr_highlevel);
}