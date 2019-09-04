#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {TYPE_3__ pb; } ;
typedef  TYPE_1__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_16_ANSI ; 
 int av_bswap16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  put_bits (TYPE_3__*,int,int) ; 
 int put_bits_count (TYPE_3__*) ; 

__attribute__((used)) static void write_frame_footer(FlacEncodeContext *s)
{
    int crc;
    flush_put_bits(&s->pb);
    crc = av_bswap16(av_crc(av_crc_get_table(AV_CRC_16_ANSI), 0, s->pb.buf,
                            put_bits_count(&s->pb)>>3));
    put_bits(&s->pb, 16, crc);
    flush_put_bits(&s->pb);
}