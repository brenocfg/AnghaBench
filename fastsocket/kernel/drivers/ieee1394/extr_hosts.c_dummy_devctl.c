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
struct hpsb_host {int dummy; } ;
typedef  enum devctl_cmd { ____Placeholder_devctl_cmd } devctl_cmd ;

/* Variables and functions */

__attribute__((used)) static int dummy_devctl(struct hpsb_host *h, enum devctl_cmd c, int arg)
{
	return -1;
}