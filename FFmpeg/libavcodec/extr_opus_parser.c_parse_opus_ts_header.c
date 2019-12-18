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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int const*,int) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const uint8_t *parse_opus_ts_header(const uint8_t *start, int *payload_len, int buf_len)
{
    const uint8_t *buf = start + 1;
    int start_trim_flag, end_trim_flag, control_extension_flag, control_extension_length;
    uint8_t flags;
    uint64_t payload_len_tmp;

    GetByteContext gb;
    bytestream2_init(&gb, buf, buf_len);

    flags = bytestream2_get_byte(&gb);
    start_trim_flag        = (flags >> 4) & 1;
    end_trim_flag          = (flags >> 3) & 1;
    control_extension_flag = (flags >> 2) & 1;

    payload_len_tmp = *payload_len = 0;
    while (bytestream2_peek_byte(&gb) == 0xff)
        payload_len_tmp += bytestream2_get_byte(&gb);

    payload_len_tmp += bytestream2_get_byte(&gb);

    if (start_trim_flag)
        bytestream2_skip(&gb, 2);
    if (end_trim_flag)
        bytestream2_skip(&gb, 2);
    if (control_extension_flag) {
        control_extension_length = bytestream2_get_byte(&gb);
        bytestream2_skip(&gb, control_extension_length);
    }

    if (bytestream2_tell(&gb) + payload_len_tmp > buf_len)
        return NULL;

    *payload_len = payload_len_tmp;

    return buf + bytestream2_tell(&gb);
}