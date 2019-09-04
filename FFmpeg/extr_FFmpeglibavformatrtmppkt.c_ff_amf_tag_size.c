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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int amf_tag_skip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

int ff_amf_tag_size(const uint8_t *data, const uint8_t *data_end)
{
    GetByteContext gb;
    int ret;

    if (data >= data_end)
        return -1;

    bytestream2_init(&gb, data, data_end - data);

    ret = amf_tag_skip(&gb);
    if (ret < 0 || bytestream2_get_bytes_left(&gb) <= 0)
        return -1;
    av_assert0(bytestream2_tell(&gb) >= 0 && bytestream2_tell(&gb) <= data_end - data);
    return bytestream2_tell(&gb);
}