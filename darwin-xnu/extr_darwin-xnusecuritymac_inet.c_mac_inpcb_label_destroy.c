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
struct inpcb {int /*<<< orphan*/ * inp_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_inpcb_label_free (int /*<<< orphan*/ *) ; 

void
mac_inpcb_label_destroy(struct inpcb *inp)
{

	mac_inpcb_label_free(inp->inp_label);
	inp->inp_label = NULL;
}