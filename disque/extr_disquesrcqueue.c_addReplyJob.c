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
struct TYPE_3__ {int /*<<< orphan*/  num_deliv; int /*<<< orphan*/  num_nacks; int /*<<< orphan*/  body; int /*<<< orphan*/  id; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int GETJOB_FLAG_WITHCOUNTERS ; 
 int /*<<< orphan*/  JOB_ID_LEN ; 
 int /*<<< orphan*/  addReplyBulk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

void addReplyJob(client *c, job *j, int flags) {
    int bulklen = 3;

    if (flags & GETJOB_FLAG_WITHCOUNTERS) bulklen += 4;
    addReplyMultiBulkLen(c,bulklen);

    addReplyBulk(c,j->queue);
    addReplyBulkCBuffer(c,j->id,JOB_ID_LEN);
    addReplyBulkCBuffer(c,j->body,sdslen(j->body));
    /* Job additional information is returned as key-value pairs. */
    if (flags & GETJOB_FLAG_WITHCOUNTERS) {
        addReplyBulkCString(c,"nacks");
        addReplyLongLong(c,j->num_nacks);

        addReplyBulkCString(c,"additional-deliveries");
        addReplyLongLong(c,j->num_deliv);
    }
}