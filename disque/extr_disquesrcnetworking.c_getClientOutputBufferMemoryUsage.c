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
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_3__ {unsigned long reply_bytes; int /*<<< orphan*/  reply; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 unsigned long listLength (int /*<<< orphan*/ ) ; 

unsigned long getClientOutputBufferMemoryUsage(client *c) {
    unsigned long list_item_size = sizeof(listNode)+5;
    /* The +5 above means we assume an sds16 hdr, may not be true
     * but is not going to be a problem. */

    return c->reply_bytes + (list_item_size*listLength(c->reply));
}