#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* deallocate ) (unsigned char*) ;scalar_t__ (* allocate ) (size_t) ;scalar_t__ (* reallocate ) (unsigned char*,size_t) ;} ;
struct TYPE_5__ {unsigned char* buffer; size_t length; size_t offset; TYPE_1__ hooks; scalar_t__ noalloc; } ;
typedef  TYPE_2__ printbuffer ;

/* Variables and functions */
 size_t LLONG_MAX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 scalar_t__ stub1 (unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (unsigned char*) ; 
 scalar_t__ stub3 (size_t) ; 
 int /*<<< orphan*/  stub4 (unsigned char*) ; 
 int /*<<< orphan*/  stub5 (unsigned char*) ; 

__attribute__((used)) static unsigned char* ensure(printbuffer * const p, size_t needed)
{
    unsigned char *newbuffer = NULL;
    size_t newsize = 0;

    if ((p == NULL) || (p->buffer == NULL))
    {
        return NULL;
    }

    if ((p->length > 0) && (p->offset >= p->length))
    {
        /* make sure that offset is valid */
        return NULL;
    }

    if (needed > LLONG_MAX)
    {
        /* sizes bigger than LLONG_MAX are currently not supported */
        return NULL;
    }

    needed += p->offset + 1;
    if (needed <= p->length)
    {
        return p->buffer + p->offset;
    }

    if (p->noalloc) {
        return NULL;
    }

    /* calculate new buffer size */
    if (needed > (LLONG_MAX / 2))
    {
        /* overflow of int, use LLONG_MAX if possible */
        if (needed <= LLONG_MAX)
        {
            newsize = LLONG_MAX;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        newsize = needed * 2;
    }

    if (p->hooks.reallocate != NULL)
    {
        /* reallocate with realloc if available */
        newbuffer = (unsigned char*)p->hooks.reallocate(p->buffer, newsize);
        if (newbuffer == NULL)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }
    }
    else
    {
        /* otherwise reallocate manually */
        newbuffer = (unsigned char*)p->hooks.allocate(newsize);
        if (!newbuffer)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }
        if (newbuffer)
        {
            memcpy(newbuffer, p->buffer, p->offset + 1);
        }
        p->hooks.deallocate(p->buffer);
    }
    p->length = newsize;
    p->buffer = newbuffer;

    return newbuffer + p->offset;
}