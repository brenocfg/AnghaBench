#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct arg_hdr {int /*<<< orphan*/  (* errorfn ) (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ;} ;
struct arg_end {int count; int /*<<< orphan*/ * argval; int /*<<< orphan*/ * error; scalar_t__* parent; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_TRACE (char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void arg_print_errors(FILE * fp, struct arg_end * end, const char * progname)
{
    int i;
    ARG_TRACE(("arg_errors()\n"));
    for (i = 0; i < end->count; i++)
    {
        struct arg_hdr *errorparent = (struct arg_hdr *)(end->parent[i]);
        if (errorparent->errorfn)
            errorparent->errorfn(end->parent[i],
                                 fp,
                                 end->error[i],
                                 end->argval[i],
                                 progname);
    }
}