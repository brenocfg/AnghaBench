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
struct TYPE_2__ {char const* shortopts; char const* longopts; char const* datatype; char const* glossary; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_int* parent; int /*<<< orphan*/  flag; } ;
struct arg_int {int* ival; scalar_t__ count; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_scanfn ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;
typedef  int /*<<< orphan*/  arg_checkfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_HASVALUE ; 
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_int_checkfn ; 
 scalar_t__ arg_int_errorfn ; 
 scalar_t__ arg_int_resetfn ; 
 scalar_t__ arg_int_scanfn ; 
 scalar_t__ malloc (size_t) ; 

struct arg_int * arg_intn(
    const char *shortopts,
    const char *longopts,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary)
{
    size_t nbytes;
    struct arg_int *result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(struct arg_int)    /* storage for struct arg_int */
             + maxcount * sizeof(int); /* storage for ival[maxcount] array */

    result = (struct arg_int *)malloc(nbytes);
    if (result)
    {
        /* init the arg_hdr struct */
        result->hdr.flag      = ARG_HASVALUE;
        result->hdr.shortopts = shortopts;
        result->hdr.longopts  = longopts;
        result->hdr.datatype  = datatype ? datatype : "<int>";
        result->hdr.glossary  = glossary;
        result->hdr.mincount  = mincount;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_int_resetfn;
        result->hdr.scanfn    = (arg_scanfn *)arg_int_scanfn;
        result->hdr.checkfn   = (arg_checkfn *)arg_int_checkfn;
        result->hdr.errorfn   = (arg_errorfn *)arg_int_errorfn;

        /* store the ival[maxcount] array immediately after the arg_int struct */
        result->ival  = (int *)(result + 1);
        result->count = 0;
    }
    
    ARG_TRACE(("arg_intn() returns %p\n", result));
    return result;
}