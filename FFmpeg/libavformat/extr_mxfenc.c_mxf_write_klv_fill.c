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
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int KAG_SIZE ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  klv_fill_key ; 
 unsigned int klv_fill_size (int) ; 

__attribute__((used)) static void mxf_write_klv_fill(AVFormatContext *s)
{
    unsigned pad = klv_fill_size(avio_tell(s->pb));
    if (pad) {
        avio_write(s->pb, klv_fill_key, 16);
        pad -= 16 + 4;
        klv_encode_ber4_length(s->pb, pad);
        ffio_fill(s->pb, 0, pad);
        av_assert1(!(avio_tell(s->pb) & (KAG_SIZE-1)));
    }
}