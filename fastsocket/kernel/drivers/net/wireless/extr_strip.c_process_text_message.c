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
struct strip {int sx_count; int /*<<< orphan*/ * sx_buff; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  RecvErr (char*,struct strip*) ; 
 int /*<<< orphan*/  RecvErr_Message (struct strip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_radio_address (struct strip*,int /*<<< orphan*/ *) ; 
 scalar_t__ has_prefix (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ text_equal (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void process_text_message(struct strip *strip_info)
{
	__u8 *msg = strip_info->sx_buff;
	int len = strip_info->sx_count;

	/* Check for anything that looks like it might be our radio name */
	/* (This is here for backwards compatibility with old firmware)  */
	if (len == 9 && get_radio_address(strip_info, msg) == 0)
		return;

	if (text_equal(msg, len, "OK"))
		return;		/* Ignore 'OK' responses from prior commands */
	if (text_equal(msg, len, "ERROR"))
		return;		/* Ignore 'ERROR' messages */
	if (has_prefix(msg, len, "ate0q1"))
		return;		/* Ignore character echo back from the radio */

	/* Catch other error messages */
	/* (This is here for backwards compatibility with old firmware) */
	if (has_prefix(msg, len, "ERR_")) {
		RecvErr_Message(strip_info, NULL, &msg[4], len - 4);
		return;
	}

	RecvErr("No initial *", strip_info);
}