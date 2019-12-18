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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ a53_caption_size; void** a53_caption; } ;
typedef  TYPE_1__ HEVCSEIA53Caption ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ const INT_MAX ; 
 int UINT64_C (int) ; 
 int av_reallocp (void***,scalar_t__ const) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_registered_user_data_closed_caption(HEVCSEIA53Caption *s, GetBitContext *gb,
                                                      int size)
{
    int flag;
    int user_data_type_code;
    int cc_count;

    if (size < 3)
       return AVERROR(EINVAL);

    user_data_type_code = get_bits(gb, 8);
    if (user_data_type_code == 0x3) {
        skip_bits(gb, 1); // reserved

        flag = get_bits(gb, 1); // process_cc_data_flag
        if (flag) {
            skip_bits(gb, 1);
            cc_count = get_bits(gb, 5);
            skip_bits(gb, 8); // reserved
            size -= 2;

            if (cc_count && size >= cc_count * 3) {
                const uint64_t new_size = (s->a53_caption_size + cc_count
                                           * UINT64_C(3));
                int i, ret;

                if (new_size > INT_MAX)
                    return AVERROR(EINVAL);

                /* Allow merging of the cc data from two fields. */
                ret = av_reallocp(&s->a53_caption, new_size);
                if (ret < 0)
                    return ret;

                for (i = 0; i < cc_count; i++) {
                    s->a53_caption[s->a53_caption_size++] = get_bits(gb, 8);
                    s->a53_caption[s->a53_caption_size++] = get_bits(gb, 8);
                    s->a53_caption[s->a53_caption_size++] = get_bits(gb, 8);
                }
                skip_bits(gb, 8); // marker_bits
            }
        }
    } else {
        int i;
        for (i = 0; i < size - 1; i++)
            skip_bits(gb, 8);
    }

    return 0;
}