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
typedef  int uint8_t ;
struct TYPE_3__ {int is_md5; void*** md5; } ;
typedef  TYPE_1__ HEVCSEIPictureHash ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_nal_sei_decoded_picture_hash(HEVCSEIPictureHash *s, GetBitContext *gb)
{
    int cIdx, i;
    uint8_t hash_type;
    //uint16_t picture_crc;
    //uint32_t picture_checksum;
    hash_type = get_bits(gb, 8);

    for (cIdx = 0; cIdx < 3/*((s->sps->chroma_format_idc == 0) ? 1 : 3)*/; cIdx++) {
        if (hash_type == 0) {
            s->is_md5 = 1;
            for (i = 0; i < 16; i++)
                s->md5[cIdx][i] = get_bits(gb, 8);
        } else if (hash_type == 1) {
            // picture_crc = get_bits(gb, 16);
            skip_bits(gb, 16);
        } else if (hash_type == 2) {
            // picture_checksum = get_bits_long(gb, 32);
            skip_bits(gb, 32);
        }
    }
    return 0;
}