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
struct TYPE_2__ {scalar_t__ maxcount; } ;
struct arg_int {scalar_t__ count; long* ival; TYPE_1__ hdr; } ;

/* Variables and functions */
 int EBADINT ; 
 int EMAXCOUNT ; 
 int EOVERFLOW ; 
 long INT_MAX ; 
 long INT_MIN ; 
 scalar_t__ detectsuffix (char const*,char*) ; 
 long strtol (char const*,char**,int) ; 
 long strtol0X (char const*,char const**,char,int) ; 

__attribute__((used)) static int arg_int_scanfn(struct arg_int *parent, const char *argval)
{
    int errorcode = 0;

    if (parent->count == parent->hdr.maxcount)
    {
        /* maximum number of arguments exceeded */
        errorcode = EMAXCOUNT;
    }
    else if (!argval)
    {
        /* a valid argument with no argument value was given. */
        /* This happens when an optional argument value was invoked. */
        /* leave parent arguiment value unaltered but still count the argument. */
        parent->count++;
    }
    else
    {
        long int val;
        const char *end;

        /* attempt to extract hex integer (eg: +0x123) from argval into val conversion */
        val = strtol0X(argval, &end, 'X', 16);
        if (end == argval)
        {
            /* hex failed, attempt octal conversion (eg +0o123) */
            val = strtol0X(argval, &end, 'O', 8);
            if (end == argval)
            {
                /* octal failed, attempt binary conversion (eg +0B101) */
                val = strtol0X(argval, &end, 'B', 2);
                if (end == argval)
                {
                    /* binary failed, attempt decimal conversion with no prefix (eg 1234) */
                    val = strtol(argval, (char * *)&end, 10);
                    if (end == argval)
                    {
                        /* all supported number formats failed */
                        return EBADINT;
                    }
                }
            }
        }

        /* Safety check for integer overflow. WARNING: this check    */
        /* achieves nothing on machines where size(int)==size(long). */
        if ( val > INT_MAX || val < INT_MIN )
            errorcode = EOVERFLOW;

        /* Detect any suffixes (KB,MB,GB) and multiply argument value appropriately. */
        /* We need to be mindful of integer overflows when using such big numbers.   */
        if (detectsuffix(end, "KB"))             /* kilobytes */
        {
            if ( val > (INT_MAX / 1024) || val < (INT_MIN / 1024) )
                errorcode = EOVERFLOW;          /* Overflow would occur if we proceed */
            else
                val *= 1024;                    /* 1KB = 1024 */
        }
        else if (detectsuffix(end, "MB"))        /* megabytes */
        {
            if ( val > (INT_MAX / 1048576) || val < (INT_MIN / 1048576) )
                errorcode = EOVERFLOW;          /* Overflow would occur if we proceed */
            else
                val *= 1048576;                 /* 1MB = 1024*1024 */
        }
        else if (detectsuffix(end, "GB"))        /* gigabytes */
        {
            if ( val > (INT_MAX / 1073741824) || val < (INT_MIN / 1073741824) )
                errorcode = EOVERFLOW;          /* Overflow would occur if we proceed */
            else
                val *= 1073741824;              /* 1GB = 1024*1024*1024 */
        }
        else if (!detectsuffix(end, ""))
            errorcode = EBADINT;                /* invalid suffix detected */

        /* if success then store result in parent->ival[] array */
        if (errorcode == 0)
            parent->ival[parent->count++] = val;
    }

    /* printf("%s:scanfn(%p,%p) returns %d\n",__FILE__,parent,argval,errorcode); */
    return errorcode;
}