#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* opaque; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ DynBuffer ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_flush (TYPE_2__*) ; 

int avio_get_dyn_buf(AVIOContext *s, uint8_t **pbuffer)
{
    DynBuffer *d;

    if (!s) {
        *pbuffer = NULL;
        return 0;
    }

    avio_flush(s);

    d = s->opaque;
    *pbuffer = d->buffer;

    return d->size;
}