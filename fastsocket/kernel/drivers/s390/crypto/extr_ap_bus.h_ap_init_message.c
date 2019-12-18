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
struct ap_message {int /*<<< orphan*/ * receive; scalar_t__ special; scalar_t__ length; scalar_t__ psmid; } ;

/* Variables and functions */

__attribute__((used)) static inline void ap_init_message(struct ap_message *ap_msg)
{
	ap_msg->psmid = 0;
	ap_msg->length = 0;
	ap_msg->special = 0;
	ap_msg->receive = NULL;
}