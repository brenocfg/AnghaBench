#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  job ;
struct TYPE_9__ {TYPE_1__** argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_10__ {int /*<<< orphan*/  nullbulk; } ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyJobInfo (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupJob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 TYPE_5__ shared ; 
 scalar_t__ validateJobIdOrReply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void showCommand(client *c) {
    if (validateJobIdOrReply(c,c->argv[1]->ptr,sdslen(c->argv[1]->ptr))
        == C_ERR) return;

    job *j = lookupJob(c->argv[1]->ptr);
    if (!j) {
        addReply(c,shared.nullbulk);
        return;
    }
    addReplyJobInfo(c,j);
}