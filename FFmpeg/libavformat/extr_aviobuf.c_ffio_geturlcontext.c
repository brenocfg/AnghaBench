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
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_5__ {scalar_t__ read_packet; TYPE_1__* opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ AVIOInternal ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 scalar_t__ io_read_packet ; 

URLContext* ffio_geturlcontext(AVIOContext *s)
{
    AVIOInternal *internal;
    if (!s)
        return NULL;

    internal = s->opaque;
    if (internal && s->read_packet == io_read_packet)
        return internal->h;
    else
        return NULL;
}