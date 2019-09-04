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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {void* cursor_y; void* cursor_x; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ RASCContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_mpos(AVCodecContext *avctx,
                       AVPacket *avpkt, unsigned size)
{
    RASCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    unsigned pos;

    pos = bytestream2_tell(gb);
    bytestream2_skip(gb, 8);
    s->cursor_x = bytestream2_get_le32(gb);
    s->cursor_y = bytestream2_get_le32(gb);

    bytestream2_skip(gb, size - (bytestream2_tell(gb) - pos));

    return 0;
}