#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  job ;
struct TYPE_4__ {scalar_t__ aof_state; } ;
struct TYPE_3__ {int /*<<< orphan*/ * loadjob; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int /*<<< orphan*/  OBJ_STRING ; 
 int /*<<< orphan*/  SER_STORAGE ; 
 int /*<<< orphan*/ * createObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feedAppendOnlyFile (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  serializeJob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 TYPE_1__ shared ; 

void AOFLoadJob(job *job) {
    if (server.aof_state == AOF_OFF) return;

    sds serialized = serializeJob(sdsempty(),job,SER_STORAGE);
    robj *serobj = createObject(OBJ_STRING,serialized);
    robj *argv[2] = {shared.loadjob, serobj};
    feedAppendOnlyFile(argv,2);
    decrRefCount(serobj);
}