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
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_offset; int /*<<< orphan*/  buffer; int /*<<< orphan*/  hdl; } ;
typedef  TYPE_1__ SndioData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_sndio_close (TYPE_1__*) ; 
 int /*<<< orphan*/  sio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_write_trailer(AVFormatContext *s1)
{
    SndioData *s = s1->priv_data;

    sio_write(s->hdl, s->buffer, s->buffer_offset);

    ff_sndio_close(s);

    return 0;
}