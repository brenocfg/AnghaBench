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
struct uwb_rc {int dummy; } ;
struct uwb_ie_hdr {int dummy; } ;
struct uwb_dbg_cmd_ie {int /*<<< orphan*/  len; scalar_t__ data; } ;

/* Variables and functions */
 int uwb_rc_ie_add (struct uwb_rc*,struct uwb_ie_hdr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_ie_add(struct uwb_rc *rc, struct uwb_dbg_cmd_ie *ie_to_add)
{
	return uwb_rc_ie_add(rc,
			     (const struct uwb_ie_hdr *) ie_to_add->data,
			     ie_to_add->len);
}