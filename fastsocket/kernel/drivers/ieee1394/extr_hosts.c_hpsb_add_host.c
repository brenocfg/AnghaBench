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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  highlevel_add_host (struct hpsb_host*) ; 
 scalar_t__ hpsb_default_host_entry (struct hpsb_host*) ; 

int hpsb_add_host(struct hpsb_host *host)
{
	if (hpsb_default_host_entry(host))
		return -ENOMEM;

	highlevel_add_host(host);
	return 0;
}