#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  queues; int /*<<< orphan*/ * job; scalar_t__ flags; scalar_t__ timeout; } ;
struct TYPE_10__ {int fd; int bulklen; int /*<<< orphan*/ * peerid; TYPE_1__ bpop; int /*<<< orphan*/  btype; int /*<<< orphan*/  reply; scalar_t__ obuf_soft_limit_reached_time; scalar_t__ reply_bytes; scalar_t__ authenticated; int /*<<< orphan*/  lastinteraction; int /*<<< orphan*/  ctime; scalar_t__ flags; scalar_t__ sentlen; scalar_t__ multibulklen; int /*<<< orphan*/ * lastcmd; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * argv; scalar_t__ argc; scalar_t__ reqtype; scalar_t__ querybuf_peak; int /*<<< orphan*/  querybuf; scalar_t__ bufpos; int /*<<< orphan*/ * name; scalar_t__ id; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {int /*<<< orphan*/  clients; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  next_client_id; int /*<<< orphan*/  el; scalar_t__ tcpkeepalive; } ;

/* Variables and functions */
 scalar_t__ AE_ERR ; 
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  BLOCKED_NONE ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  anetEnableTcpNoDelay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  anetKeepAlive (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  anetNonBlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dupClientReplyValue ; 
 int /*<<< orphan*/  freeClientReplyValue ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  listCreate () ; 
 int /*<<< orphan*/  listSetDupMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listSetFreeMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readQueryFromClient ; 
 int /*<<< orphan*/  sdsempty () ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  setDictType ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 TYPE_2__* zmalloc (int) ; 

client *createClient(int fd) {
    client *c = zmalloc(sizeof(client));

    /* passing -1 as fd it is possible to create a non connected client.
     * This is useful since all the commands needs to be executed
     * in the context of a client. When commands are executed in other
     * contexts (for instance a Lua script) we need a non connected client. */
    if (fd != -1) {
        anetNonBlock(NULL,fd);
        anetEnableTcpNoDelay(NULL,fd);
        if (server.tcpkeepalive)
            anetKeepAlive(NULL,fd,server.tcpkeepalive);
        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
            readQueryFromClient, c) == AE_ERR)
        {
            close(fd);
            zfree(c);
            return NULL;
        }
    }

    c->id = server.next_client_id++;
    c->fd = fd;
    c->name = NULL;
    c->bufpos = 0;
    c->querybuf = sdsempty();
    c->querybuf_peak = 0;
    c->reqtype = 0;
    c->argc = 0;
    c->argv = NULL;
    c->cmd = c->lastcmd = NULL;
    c->multibulklen = 0;
    c->bulklen = -1;
    c->sentlen = 0;
    c->flags = 0;
    c->ctime = c->lastinteraction = server.unixtime;
    c->authenticated = 0;
    c->reply = listCreate();
    c->reply_bytes = 0;
    c->obuf_soft_limit_reached_time = 0;
    listSetFreeMethod(c->reply,freeClientReplyValue);
    listSetDupMethod(c->reply,dupClientReplyValue);
    c->btype = BLOCKED_NONE;
    c->bpop.timeout = 0;
    c->bpop.flags = 0;
    c->bpop.job = NULL;
    c->bpop.queues = dictCreate(&setDictType,NULL);
    c->peerid = NULL;
    if (fd != -1) listAddNodeTail(server.clients,c);
    return c;
}