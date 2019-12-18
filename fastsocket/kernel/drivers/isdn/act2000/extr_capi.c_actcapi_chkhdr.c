#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cmd; scalar_t__ subcmd; } ;
struct TYPE_8__ {int applicationID; int len; TYPE_1__ cmd; } ;
typedef  TYPE_3__ actcapi_msghdr ;
typedef  int /*<<< orphan*/  act2000_card ;
struct TYPE_7__ {scalar_t__ cmd; scalar_t__ subcmd; } ;
struct TYPE_9__ {TYPE_2__ cmd; } ;

/* Variables and functions */
 int num_valid_imsg ; 
 TYPE_4__* valid_msg ; 

int
actcapi_chkhdr(act2000_card * card, actcapi_msghdr *hdr)
{
	int i;

	if (hdr->applicationID != 1)
		return 0;
	if (hdr->len < 9)
		return 0;
	for (i = 0; i < num_valid_imsg; i++)
		if ((hdr->cmd.cmd == valid_msg[i].cmd.cmd) &&
		    (hdr->cmd.subcmd == valid_msg[i].cmd.subcmd)) {
			return (i?1:2);
		}
	return 0;
}