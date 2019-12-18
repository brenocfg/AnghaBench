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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int leb128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int parse_obu_header(const uint8_t *buf, int buf_size,
                                   int64_t *obu_size, int *start_pos, int *type,
                                   int *temporal_id, int *spatial_id)
{
    GetBitContext gb;
    int ret, extension_flag, has_size_flag;
    int64_t size;

    ret = init_get_bits8(&gb, buf, FFMIN(buf_size, 2 + 8)); // OBU header fields + max leb128 length
    if (ret < 0)
        return ret;

    if (get_bits1(&gb) != 0) // obu_forbidden_bit
        return AVERROR_INVALIDDATA;

    *type      = get_bits(&gb, 4);
    extension_flag = get_bits1(&gb);
    has_size_flag  = get_bits1(&gb);
    skip_bits1(&gb); // obu_reserved_1bit

    if (extension_flag) {
        *temporal_id = get_bits(&gb, 3);
        *spatial_id  = get_bits(&gb, 2);
        skip_bits(&gb, 3); // extension_header_reserved_3bits
    } else {
        *temporal_id = *spatial_id = 0;
    }

    *obu_size  = has_size_flag ? leb128(&gb)
                               : buf_size - 1 - extension_flag;

    if (get_bits_left(&gb) < 0)
        return AVERROR_INVALIDDATA;

    *start_pos = get_bits_count(&gb) / 8;

    size = *obu_size + *start_pos;

    if (size > buf_size)
        return AVERROR_INVALIDDATA;

    return size;
}