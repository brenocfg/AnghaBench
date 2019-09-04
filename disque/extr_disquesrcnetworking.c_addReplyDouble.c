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
typedef  int /*<<< orphan*/  sbuf ;
typedef  int /*<<< orphan*/  dbuf ;
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyString (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ isinf (double) ; 
 int snprintf (char*,int,char*,int,...) ; 

void addReplyDouble(client *c, double d) {
    char dbuf[128], sbuf[128];
    int dlen, slen;
    if (isinf(d)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        addReplyBulkCString(c, d > 0 ? "inf" : "-inf");
    } else {
        dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
        slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
        addReplyString(c,sbuf,slen);
    }
}