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
struct TYPE_2__ {char const* datatype; char const* glossary; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_rem* parent; int /*<<< orphan*/ * longopts; int /*<<< orphan*/ * shortopts; scalar_t__ flag; } ;
struct arg_rem {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ malloc (int) ; 

struct arg_rem *arg_rem(const char *datatype, const char *glossary)
{
    struct arg_rem *result = (struct arg_rem *)malloc(sizeof(struct arg_rem));
    if (result)
    {
        result->hdr.flag = 0;
        result->hdr.shortopts = NULL;
        result->hdr.longopts = NULL;
        result->hdr.datatype = datatype;
        result->hdr.glossary = glossary;
        result->hdr.mincount = 1;
        result->hdr.maxcount = 1;
        result->hdr.parent = result;
        result->hdr.resetfn = NULL;
        result->hdr.scanfn = NULL;
        result->hdr.checkfn = NULL;
        result->hdr.errorfn = NULL;
    }

    ARG_TRACE(("arg_rem() returns %p\n", result));
    return result;
}