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
struct tm {int dummy; } ;
struct TYPE_2__ {char const* shortopts; char const* longopts; char const* datatype; char const* glossary; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_date* parent; int /*<<< orphan*/  flag; } ;
struct arg_date {char const* format; scalar_t__ count; struct tm* tmval; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_scanfn ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;
typedef  int /*<<< orphan*/  arg_checkfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_HASVALUE ; 
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_date_checkfn ; 
 scalar_t__ arg_date_errorfn ; 
 scalar_t__ arg_date_resetfn ; 
 scalar_t__ arg_date_scanfn ; 
 scalar_t__ calloc (int,size_t) ; 

struct arg_date * arg_daten(
    const char * shortopts,
    const char * longopts,
    const char * format,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary)
{
    size_t nbytes;
    struct arg_date *result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    /* default time format is the national date format for the locale */
    if (!format)
        format = "%x";

    nbytes = sizeof(struct arg_date)         /* storage for struct arg_date */
        + maxcount * sizeof(struct tm);    /* storage for tmval[maxcount] array */

    /* allocate storage for the arg_date struct + tmval[] array.    */
    /* we use calloc because we want the tmval[] array zero filled. */
    result = (struct arg_date *)calloc(1, nbytes);
    if (result)
    {
        /* init the arg_hdr struct */
        result->hdr.flag      = ARG_HASVALUE;
        result->hdr.shortopts = shortopts;
        result->hdr.longopts  = longopts;
        result->hdr.datatype  = datatype ? datatype : format;
        result->hdr.glossary  = glossary;
        result->hdr.mincount  = mincount;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_date_resetfn;
        result->hdr.scanfn    = (arg_scanfn *)arg_date_scanfn;
        result->hdr.checkfn   = (arg_checkfn *)arg_date_checkfn;
        result->hdr.errorfn   = (arg_errorfn *)arg_date_errorfn;

        /* store the tmval[maxcount] array immediately after the arg_date struct */
        result->tmval  = (struct tm *)(result + 1);

        /* init the remaining arg_date member variables */
        result->count = 0;
        result->format = format;
    }

    ARG_TRACE(("arg_daten() returns %p\n", result));
    return result;
}