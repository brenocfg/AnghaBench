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
struct TYPE_2__ {char const* shortopts; char const* longopts; char const* glossary; char const* datatype; int mincount; int maxcount; int /*<<< orphan*/ * errorfn; int /*<<< orphan*/ * checkfn; int /*<<< orphan*/ * scanfn; int /*<<< orphan*/ * resetfn; struct arg_file* parent; int /*<<< orphan*/  flag; } ;
struct arg_file {char const** filename; char** basename; char** extension; scalar_t__ count; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  arg_scanfn ;
typedef  int /*<<< orphan*/  arg_resetfn ;
typedef  int /*<<< orphan*/  arg_errorfn ;
typedef  int /*<<< orphan*/  arg_checkfn ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_HASVALUE ; 
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 scalar_t__ arg_file_checkfn ; 
 scalar_t__ arg_file_errorfn ; 
 scalar_t__ arg_file_resetfn ; 
 scalar_t__ arg_file_scanfn ; 
 scalar_t__ malloc (size_t) ; 

struct arg_file * arg_filen(
    const char * shortopts,
    const char * longopts,
    const char *datatype,
    int mincount,
    int maxcount,
    const char *glossary)
{
    size_t nbytes;
    struct arg_file *result;

    /* foolproof things by ensuring maxcount is not less than mincount */
    maxcount = (maxcount < mincount) ? mincount : maxcount;

    nbytes = sizeof(struct arg_file)      /* storage for struct arg_file */
             + sizeof(char *) * maxcount  /* storage for filename[maxcount] array */
             + sizeof(char *) * maxcount  /* storage for basename[maxcount] array */
             + sizeof(char *) * maxcount; /* storage for extension[maxcount] array */

    result = (struct arg_file *)malloc(nbytes);
    if (result)
    {
        int i;

        /* init the arg_hdr struct */
        result->hdr.flag      = ARG_HASVALUE;
        result->hdr.shortopts = shortopts;
        result->hdr.longopts  = longopts;
        result->hdr.glossary  = glossary;
        result->hdr.datatype  = datatype ? datatype : "<file>";
        result->hdr.mincount  = mincount;
        result->hdr.maxcount  = maxcount;
        result->hdr.parent    = result;
        result->hdr.resetfn   = (arg_resetfn *)arg_file_resetfn;
        result->hdr.scanfn    = (arg_scanfn *)arg_file_scanfn;
        result->hdr.checkfn   = (arg_checkfn *)arg_file_checkfn;
        result->hdr.errorfn   = (arg_errorfn *)arg_file_errorfn;

        /* store the filename,basename,extension arrays immediately after the arg_file struct */
        result->filename  = (const char * *)(result + 1);
        result->basename  = result->filename + maxcount;
        result->extension = result->basename + maxcount;
        result->count = 0;

        /* foolproof the string pointers by initialising them with empty strings */
        for (i = 0; i < maxcount; i++)
        {
            result->filename[i] = "";
            result->basename[i] = "";
            result->extension[i] = "";
        }
    }
    
    ARG_TRACE(("arg_filen() returns %p\n", result));
    return result;
}