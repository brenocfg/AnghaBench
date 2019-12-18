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
struct TYPE_2__ {size_t maxcount; } ;
struct arg_end {size_t count; int* error; char const** argval; TYPE_1__ hdr; struct arg_end** parent; } ;

/* Variables and functions */
 int ARG_ELIMIT ; 

__attribute__((used)) static
void arg_register_error(struct arg_end *end,
                        void *parent,
                        int error,
                        const char *argval)
{
    /* printf("arg_register_error(%p,%p,%d,%s)\n",end,parent,error,argval); */
    if (end->count < end->hdr.maxcount)
    {
        end->error[end->count] = error;
        end->parent[end->count] = parent;
        end->argval[end->count] = argval;
        end->count++;
    }
    else
    {
        end->error[end->hdr.maxcount - 1]  = ARG_ELIMIT;
        end->parent[end->hdr.maxcount - 1] = end;
        end->argval[end->hdr.maxcount - 1] = NULL;
    }
}