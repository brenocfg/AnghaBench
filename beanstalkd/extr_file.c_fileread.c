#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  Job ;
typedef  TYPE_1__ File ;

/* Variables and functions */
#define  Walver 129 
#define  Walver5 128 
 int /*<<< orphan*/  filedecref (TYPE_1__*) ; 
 int /*<<< orphan*/  fileincref (TYPE_1__*) ; 
 int /*<<< orphan*/  readfull (TYPE_1__*,int*,int,int*,char*) ; 
 int /*<<< orphan*/  readrec (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  readrec5 (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int) ; 

int
fileread(File *f, Job *list)
{
    int err = 0, v;

    if (!readfull(f, &v, sizeof(v), &err, "version")) {
        return err;
    }
    switch (v) {
    case Walver:
        fileincref(f);
        while (readrec(f, list, &err));
        filedecref(f);
        return err;
    case Walver5:
        fileincref(f);
        while (readrec5(f, list, &err));
        filedecref(f);
        return err;
    }

    warnx("%s: unknown version: %d", f->path, v);
    return 1;
}