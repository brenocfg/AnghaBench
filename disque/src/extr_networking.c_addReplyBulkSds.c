#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_2__ {int /*<<< orphan*/  crlf; } ;

/* Variables and functions */
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplySds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 
 TYPE_1__ shared ; 

void addReplyBulkSds(client *c, sds s)  {
    addReplySds(c,sdscatfmt(sdsempty(),"$%u\r\n",
        (unsigned long)sdslen(s)));
    addReplySds(c,s);
    addReply(c,shared.crlf);
}