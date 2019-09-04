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
struct client {int /*<<< orphan*/  reply; int /*<<< orphan*/  querybuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct client*) ; 

void freeFakeClient(struct client *c) {
    sdsfree(c->querybuf);
    listRelease(c->reply);
    zfree(c);
}