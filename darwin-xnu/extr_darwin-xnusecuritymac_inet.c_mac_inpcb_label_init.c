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
 int ENOMEM ; 
 int /*<<< orphan*/ * mac_inpcb_label_alloc (int) ; 

int
mac_inpcb_label_init(struct inpcb *inp, int flag)
{

	inp->inp_label = mac_inpcb_label_alloc(flag);
	if (inp->inp_label == NULL)
		return (ENOMEM);
	return (0);
}