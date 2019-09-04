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
struct TYPE_8__ {int argc; long long duration; scalar_t__ id; int /*<<< orphan*/  time; TYPE_2__** argv; } ;
typedef  TYPE_1__ slowlogEntry ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_10__ {int /*<<< orphan*/  slowlog_entry_id; } ;

/* Variables and functions */
 scalar_t__ OBJ_STRING ; 
 int SLOWLOG_ENTRY_MAX_ARGC ; 
 unsigned long SLOWLOG_ENTRY_MAX_STRING ; 
 void* createObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incrRefCount (TYPE_2__*) ; 
 scalar_t__ sdsEncodedObject (TYPE_2__*) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  sdsempty () ; 
 unsigned long sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnewlen (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 void* zmalloc (int) ; 

slowlogEntry *slowlogCreateEntry(robj **argv, int argc, long long duration) {
    slowlogEntry *se = zmalloc(sizeof(*se));
    int j, slargc = argc;

    if (slargc > SLOWLOG_ENTRY_MAX_ARGC) slargc = SLOWLOG_ENTRY_MAX_ARGC;
    se->argc = slargc;
    se->argv = zmalloc(sizeof(robj*)*slargc);
    for (j = 0; j < slargc; j++) {
        /* Logging too many arguments is a useless memory waste, so we stop
         * at SLOWLOG_ENTRY_MAX_ARGC, but use the last argument to specify
         * how many remaining arguments there were in the original command. */
        if (slargc != argc && j == slargc-1) {
            se->argv[j] = createObject(OBJ_STRING,
                sdscatprintf(sdsempty(),"... (%d more arguments)",
                argc-slargc+1));
        } else {
            /* Trim too long strings as well... */
            if (argv[j]->type == OBJ_STRING &&
                sdsEncodedObject(argv[j]) &&
                sdslen(argv[j]->ptr) > SLOWLOG_ENTRY_MAX_STRING)
            {
                sds s = sdsnewlen(argv[j]->ptr, SLOWLOG_ENTRY_MAX_STRING);

                s = sdscatprintf(s,"... (%lu more bytes)",
                    (unsigned long)
                    sdslen(argv[j]->ptr) - SLOWLOG_ENTRY_MAX_STRING);
                se->argv[j] = createObject(OBJ_STRING,s);
            } else {
                se->argv[j] = argv[j];
                incrRefCount(argv[j]);
            }
        }
    }
    se->time = time(NULL);
    se->duration = duration;
    se->id = server.slowlog_entry_id++;
    return se;
}