#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hdl; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ SndioData ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sio_close (scalar_t__) ; 

int ff_sndio_close(SndioData *s)
{
    av_freep(&s->buffer);

    if (s->hdl)
        sio_close(s->hdl);

    return 0;
}