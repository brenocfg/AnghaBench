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
struct hpsb_highlevel {int /*<<< orphan*/  name; } ;
struct hl_host_info {void* data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HPSB_ERR (char*,int /*<<< orphan*/ ) ; 
 struct hl_host_info* hl_get_hostinfo (struct hpsb_highlevel*,struct hpsb_host*) ; 

int hpsb_set_hostinfo(struct hpsb_highlevel *hl, struct hpsb_host *host,
		      void *data)
{
	struct hl_host_info *hi;

	hi = hl_get_hostinfo(hl, host);
	if (hi) {
		if (!hi->size && !hi->data) {
			hi->data = data;
			return 0;
		} else
			HPSB_ERR("%s called hpsb_set_hostinfo when hostinfo "
				 "already has data", hl->name);
	} else
		HPSB_ERR("%s called hpsb_set_hostinfo when no hostinfo exists",
			 hl->name);
	return -EINVAL;
}