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
struct TYPE_2__ {char const* shortopts; char const* longopts; char const* glossary; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_lit* parent; int /*<<< orphan*/ * datatype; scalar_t__ flag; } ;
struct arg_lit {scalar_t__ count; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_scanfn ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;
typedef  int /*<<< orphan*/  arg_checkfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_lit_checkfn ; 
 scalar_t__ arg_lit_errorfn ; 
 scalar_t__ arg_lit_resetfn ; 
 scalar_t__ arg_lit_scanfn ; 
 scalar_t__ malloc (int) ; 

struct arg_lit * arg_litn(
    const char *shortopts,
    const char *longopts,
    int mincount,
    int maxcount,
    const char *glossary)
{
    struct arg_lit *result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    result = (struct arg_lit *)malloc(sizeof(struct arg_lit));
    if (result)
    {
        /* init the arg_hdr struct */
        result->hdr.flag      = 0;
        result->hdr.shortopts = shortopts;
        result->hdr.longopts  = longopts;
        result->hdr.datatype  = NULL;
        result->hdr.glossary  = glossary;
        result->hdr.mincount  = mincount;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_lit_resetfn;
        result->hdr.scanfn    = (arg_scanfn *)arg_lit_scanfn;
        result->hdr.checkfn   = (arg_checkfn *)arg_lit_checkfn;
        result->hdr.errorfn   = (arg_errorfn *)arg_lit_errorfn;

        /* init local variables */
        result->count = 0;
    }
    
    ARG_TRACE(("arg_litn() returns %p\n", result));
    return result;
}