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
struct hpsb_iso {int dummy; } ;
typedef  enum isoctl_cmd { ____Placeholder_isoctl_cmd } isoctl_cmd ;

/* Variables and functions */

__attribute__((used)) static int dummy_isoctl(struct hpsb_iso *iso, enum isoctl_cmd command,
			unsigned long arg)
{
	return -1;
}