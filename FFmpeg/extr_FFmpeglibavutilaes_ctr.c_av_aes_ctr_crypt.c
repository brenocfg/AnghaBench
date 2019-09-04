#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AVAESCTR {scalar_t__ block_offset; int /*<<< orphan*/ * encrypted_counter; scalar_t__ counter; int /*<<< orphan*/  aes; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/ * FFMIN (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_aes_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_aes_ctr_increment_be64 (scalar_t__) ; 

void av_aes_ctr_crypt(struct AVAESCTR *a, uint8_t *dst, const uint8_t *src, int count)
{
    const uint8_t* src_end = src + count;
    const uint8_t* cur_end_pos;
    uint8_t* encrypted_counter_pos;

    while (src < src_end) {
        if (a->block_offset == 0) {
            av_aes_crypt(a->aes, a->encrypted_counter, a->counter, 1, NULL, 0);

            av_aes_ctr_increment_be64(a->counter + 8);
        }

        encrypted_counter_pos = a->encrypted_counter + a->block_offset;
        cur_end_pos = src + AES_BLOCK_SIZE - a->block_offset;
        cur_end_pos = FFMIN(cur_end_pos, src_end);

        a->block_offset += cur_end_pos - src;
        a->block_offset &= (AES_BLOCK_SIZE - 1);

        while (src < cur_end_pos) {
            *dst++ = *src++ ^ *encrypted_counter_pos++;
        }
    }
}