#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  dir; scalar_t__ use; } ;
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* prev; } ;
struct TYPE_9__ {TYPE_3__ wal; } ;
typedef  TYPE_1__ Server ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int prot_replay (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  twarnx (char*,...) ; 
 int /*<<< orphan*/  waldirlock (TYPE_3__*) ; 
 int /*<<< orphan*/  walinit (TYPE_3__*,TYPE_2__*) ; 

void srv_acquire_wal(Server *s) {
    if (s->wal.use) {
        // We want to make sure that only one beanstalkd tries
        // to use the wal directory at a time. So acquire a lock
        // now and never release it.
        if (!waldirlock(&s->wal)) {
            twarnx("failed to lock wal dir %s", s->wal.dir);
            exit(10);
        }

        Job list = {.prev=NULL, .next=NULL};
        list.prev = list.next = &list;
        walinit(&s->wal, &list);
        int ok = prot_replay(s, &list);
        if (!ok) {
            twarnx("failed to replay log");
            exit(1);
        }
    }
}