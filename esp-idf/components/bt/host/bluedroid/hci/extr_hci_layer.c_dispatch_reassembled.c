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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SIG_BTU_HCI_MSG ; 
 int btu_task_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch_reassembled(BT_HDR *packet)
{
    // Events should already have been dispatched before this point
    //Tell Up-layer received packet.
    if (btu_task_post(SIG_BTU_HCI_MSG, packet, OSI_THREAD_MAX_TIMEOUT) == false) {
        osi_free(packet);
    }
}