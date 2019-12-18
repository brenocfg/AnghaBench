#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int value; int /*<<< orphan*/  prob; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ PTable ;
typedef  TYPE_2__ HuffEntry ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  calculate_codes (TYPE_2__*) ; 
 int /*<<< orphan*/  count_usage (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  magy_huffman_compute_bits (TYPE_1__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encode_table(AVCodecContext *avctx, uint8_t *dst,
                        int width, int height,
                        PutBitContext *pb, HuffEntry *he)
{
    PTable counts[256] = { {0} };
    int i;

    count_usage(dst, width, height, counts);

    for (i = 0; i < 256; i++) {
        counts[i].prob++;
        counts[i].value = 255 - i;
    }

    magy_huffman_compute_bits(counts, he, 256, 12);

    calculate_codes(he);

    for (i = 0; i < 256; i++) {
        put_bits(pb, 1, 0);
        put_bits(pb, 7, he[i].len);
    }

    return 0;
}