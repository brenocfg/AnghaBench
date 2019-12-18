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
struct TYPE_2__ {int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_end* parent; int /*<<< orphan*/ * glossary; int /*<<< orphan*/ * datatype; int /*<<< orphan*/ * longopts; int /*<<< orphan*/ * shortopts; int /*<<< orphan*/  flag; } ;
struct arg_end {int* error; void** parent; char const** argval; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_TERMINATOR ; 
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_end_errorfn ; 
 scalar_t__ arg_end_resetfn ; 
 scalar_t__ malloc (size_t) ; 

struct arg_end * arg_end(int maxcount)
{
    size_t nbytes;
    struct arg_end *result;

    nbytes = sizeof(struct arg_end)
             + maxcount * sizeof(int)     /* storage for int error[maxcount] array*/
             + maxcount * sizeof(void *)  /* storage for void* parent[maxcount] array */
             + maxcount * sizeof(char *); /* storage for char* argval[maxcount] array */

    result = (struct arg_end *)malloc(nbytes);
    if (result)
    {
        /* init the arg_hdr struct */
        result->hdr.flag      = ARG_TERMINATOR;
        result->hdr.shortopts = NULL;
        result->hdr.longopts  = NULL;
        result->hdr.datatype  = NULL;
        result->hdr.glossary  = NULL;
        result->hdr.mincount  = 1;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_end_resetfn;
        result->hdr.scanfn    = NULL;
        result->hdr.checkfn   = NULL;
        result->hdr.errorfn   = (arg_errorfn *)arg_end_errorfn;

        /* store error[maxcount] array immediately after struct arg_end */
        result->error = (int *)(result + 1);

        /* store parent[maxcount] array immediately after error[] array */
        result->parent = (void * *)(result->error + maxcount );

        /* store argval[maxcount] array immediately after parent[] array */
        result->argval = (const char * *)(result->parent + maxcount );
    }

    ARG_TRACE(("arg_end(%d) returns %p\n", maxcount, result));
    return result;
}