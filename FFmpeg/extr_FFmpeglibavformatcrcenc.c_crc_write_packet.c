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
struct AVFormatContext {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  crcval; } ;
typedef  TYPE_1__ CRCState ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_adler32_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crc_write_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    CRCState *crc = s->priv_data;
    crc->crcval = av_adler32_update(crc->crcval, pkt->data, pkt->size);
    return 0;
}