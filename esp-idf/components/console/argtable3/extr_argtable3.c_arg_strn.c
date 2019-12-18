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
struct TYPE_2__ {char const* shortopts; char const* longopts; char const* datatype; char const* glossary; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_str* parent; int /*<<< orphan*/  flag; } ;
struct arg_str {char const** sval; scalar_t__ count; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_scanfn ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;
typedef  int /*<<< orphan*/  arg_checkfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_HASVALUE ; 
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_str_checkfn ; 
 scalar_t__ arg_str_errorfn ; 
 scalar_t__ arg_str_resetfn ; 
 scalar_t__ arg_str_scanfn ; 
 scalar_t__ malloc (size_t) ; 

struct arg_str * arg_strn(
    const char *shortopts,
    const char *longopts,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary)
{
    size_t nbytes;
    struct arg_str *result;

    /* should not allow this stupid error */
    /* we should return an error code warning this logic error */
    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(struct arg_str)     /* storage for struct arg_str */
             + maxcount * sizeof(char *); /* storage for sval[maxcount] array */

    result = (struct arg_str *)malloc(nbytes);
    if (result)
    {
        int i;

        /* init the arg_hdr struct */
        result->hdr.flag      = ARG_HASVALUE;
        result->hdr.shortopts = shortopts;
        result->hdr.longopts  = longopts;
        result->hdr.datatype  = datatype ? datatype : "<string>";
        result->hdr.glossary  = glossary;
        result->hdr.mincount  = mincount;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_str_resetfn;
        result->hdr.scanfn    = (arg_scanfn *)arg_str_scanfn;
        result->hdr.checkfn   = (arg_checkfn *)arg_str_checkfn;
        result->hdr.errorfn   = (arg_errorfn *)arg_str_errorfn;

        /* store the sval[maxcount] array immediately after the arg_str struct */
        result->sval  = (const char * *)(result + 1);
        result->count = 0;

        /* foolproof the string pointers by initialising them to reference empty strings */
        for (i = 0; i < maxcount; i++)
            result->sval[i] = "";
    }
    
    ARG_TRACE(("arg_strn() returns %p\n", result));
    return result;
}