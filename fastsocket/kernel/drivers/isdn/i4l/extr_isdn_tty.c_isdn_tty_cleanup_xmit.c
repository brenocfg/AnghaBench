#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dtmf_queue; int /*<<< orphan*/  xmit_queue; } ;
typedef  TYPE_1__ modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_tty_cleanup_xmit(modem_info * info)
{
	skb_queue_purge(&info->xmit_queue);
#ifdef CONFIG_ISDN_AUDIO
	skb_queue_purge(&info->dtmf_queue);
#endif
}