#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {scalar_t__ buffer_size; scalar_t__ buffer_offset; scalar_t__ buffer; int softpos; int /*<<< orphan*/  hdl; } ;
typedef  TYPE_1__ SndioData ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sio_eof (int /*<<< orphan*/ ) ; 
 int sio_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int audio_write_packet(AVFormatContext *s1, AVPacket *pkt)
{
    SndioData *s = s1->priv_data;
    uint8_t *buf= pkt->data;
    int size = pkt->size;
    int len, ret;

    while (size > 0) {
        len = FFMIN(s->buffer_size - s->buffer_offset, size);
        memcpy(s->buffer + s->buffer_offset, buf, len);
        buf  += len;
        size -= len;
        s->buffer_offset += len;
        if (s->buffer_offset >= s->buffer_size) {
            ret = sio_write(s->hdl, s->buffer, s->buffer_size);
            if (ret == 0 || sio_eof(s->hdl))
                return AVERROR(EIO);
            s->softpos      += ret;
            s->buffer_offset = 0;
        }
    }

    return 0;
}