#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int /*<<< orphan*/ * data; } ;
struct gss_upcall_msg {TYPE_1__ msg; int /*<<< orphan*/  uid; } ;

/* Variables and functions */

__attribute__((used)) static void gss_encode_v0_msg(struct gss_upcall_msg *gss_msg)
{
	gss_msg->msg.data = &gss_msg->uid;
	gss_msg->msg.len = sizeof(gss_msg->uid);
}