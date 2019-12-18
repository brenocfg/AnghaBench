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
struct TYPE_3__ {int /*<<< orphan*/  reply; scalar_t__ bufpos; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 

int clientHasPendingReplies(client *c) {
    return c->bufpos || listLength(c->reply);
}