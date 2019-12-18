#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct timespec {long long tv_sec; long long tv_nsec; } ;
struct sdshdr8 {int dummy; } ;
struct sdshdr64 {int dummy; } ;
struct sdshdr5 {int dummy; } ;
struct sdshdr32 {int dummy; } ;
struct sdshdr16 {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  queue ;
typedef  int /*<<< orphan*/  job ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_16__ {int argc; TYPE_2__** argv; } ;
typedef  TYPE_1__ client ;
struct TYPE_19__ {scalar_t__ aof_state; int /*<<< orphan*/  aof_filename; } ;
struct TYPE_18__ {int /*<<< orphan*/  ok; int /*<<< orphan*/  err; } ;
struct TYPE_17__ {scalar_t__ ptr; } ;

/* Variables and functions */
 scalar_t__ AOF_ON ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int RESTART_SERVER_CONFIG_REWRITE ; 
 int RESTART_SERVER_GRACEFULLY ; 
 int RESTART_SERVER_NONE ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkSds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyError (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  addReplyErrorFormat (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushAppendOnlyFile (int) ; 
 int /*<<< orphan*/  flushServerData () ; 
 scalar_t__ getLongLongFromObjectOrReply (TYPE_1__*,TYPE_2__*,long long*,int /*<<< orphan*/ *) ; 
 scalar_t__ loadAppendOnlyFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restartServer (int,long long) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsmapchars (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  sdsnewlen (char*,int) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  serverAssertWithInfo (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ shared ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 
 double strtod (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* tryObjectEncoding (TYPE_2__*) ; 
 int /*<<< orphan*/  zfree (void*) ; 
 void* zmalloc (int /*<<< orphan*/ ) ; 

void debugCommand(client *c) {
    if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"restart") ||
               !strcasecmp(c->argv[1]->ptr,"crash-and-recover"))
    {
        long long delay = 0;
        if (c->argc >= 3) {
            if (getLongLongFromObjectOrReply(c, c->argv[2], &delay, NULL)
                != C_OK) return;
            if (delay < 0) delay = 0;
        }
        int flags = !strcasecmp(c->argv[1]->ptr,"restart") ?
            (RESTART_SERVER_GRACEFULLY|RESTART_SERVER_CONFIG_REWRITE) :
             RESTART_SERVER_NONE;
        restartServer(flags,delay);
        addReplyError(c,"failed to restart the server. Check server logs.");
    } else if (!strcasecmp(c->argv[1]->ptr,"oom")) {
        void *ptr = zmalloc(ULONG_MAX); /* Should trigger an out of memory. */
        zfree(ptr);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"assert")) {
        if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
        serverAssertWithInfo(c,c->argv[0],1 == 2);
    } else if (!strcasecmp(c->argv[1]->ptr,"flushall")) {
        flushServerData();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        if (server.aof_state == AOF_ON) flushAppendOnlyFile(1);
        flushServerData();
        if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
            addReply(c,shared.err);
            return;
        }
        serverLog(LL_WARNING,"Append Only File loaded by DEBUG LOADAOF");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"sleep") && c->argc == 3) {
        double dtime = strtod(c->argv[2]->ptr,NULL);
        long long utime = dtime*1000000;
        struct timespec tv;

        tv.tv_sec = utime / 1000000;
        tv.tv_nsec = (utime % 1000000) * 1000;
        nanosleep(&tv, NULL);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"error") && c->argc == 3) {
        sds errstr = sdsnewlen("-",1);

        errstr = sdscatsds(errstr,c->argv[2]->ptr);
        errstr = sdsmapchars(errstr,"\n\r","  ",2); /* no newlines in errors. */
        errstr = sdscatlen(errstr,"\r\n",2);
        addReplySds(c,errstr);
    } else if (!strcasecmp(c->argv[1]->ptr,"structsize") && c->argc == 2) {
        sds sizes = sdsempty();
        sizes = sdscatprintf(sizes,"bits:%d ",(sizeof(void*) == 8)?64:32);
        sizes = sdscatprintf(sizes,"job:%d ", (int)sizeof(job));
        sizes = sdscatprintf(sizes,"queue:%d ", (int)sizeof(queue));
        sizes = sdscatprintf(sizes,"robj:%d ",(int)sizeof(robj));
        sizes = sdscatprintf(sizes,"dictentry:%d ",(int)sizeof(dictEntry));
        sizes = sdscatprintf(sizes,"sdshdr5:%d ",(int)sizeof(struct sdshdr5));
        sizes = sdscatprintf(sizes,"sdshdr8:%d ",(int)sizeof(struct sdshdr8));
        sizes = sdscatprintf(sizes,"sdshdr16:%d ",(int)sizeof(struct sdshdr16));
        sizes = sdscatprintf(sizes,"sdshdr32:%d ",(int)sizeof(struct sdshdr32));
        sizes = sdscatprintf(sizes,"sdshdr64:%d ",(int)sizeof(struct sdshdr64));
        addReplyBulkSds(c,sizes);
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
            (char*)c->argv[1]->ptr);
    }
}