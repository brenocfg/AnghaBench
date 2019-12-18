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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct uwb_rceb {int dummy; } ;
struct uwb_rccb {int dummy; } ;
struct uwb_rc {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __uwb_rc_cmd (struct uwb_rc*,char const*,struct uwb_rccb*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uwb_rceb**) ; 

ssize_t uwb_rc_vcmd(struct uwb_rc *rc, const char *cmd_name,
		    struct uwb_rccb *cmd, size_t cmd_size,
		    u8 expected_type, u16 expected_event,
		    struct uwb_rceb **preply)
{
	return __uwb_rc_cmd(rc, cmd_name, cmd, cmd_size, NULL, 0,
			    expected_type, expected_event, preply);
}