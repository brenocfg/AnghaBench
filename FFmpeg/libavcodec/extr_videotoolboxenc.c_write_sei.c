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
typedef  int ssize_t ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ExtraSEI ;

/* Variables and functions */
 int AVERROR_BUFFER_TOO_SMALL ; 
 int copy_emulation_prev (int /*<<< orphan*/ ,size_t,int*,int,size_t) ; 

__attribute__((used)) static int write_sei(const ExtraSEI *sei,
                     int             sei_type,
                     uint8_t        *dst,
                     size_t          dst_size)
{
    uint8_t *sei_start = dst;
    size_t remaining_sei_size = sei->size;
    size_t remaining_dst_size = dst_size;
    int header_bytes;
    int bytes_written;
    ssize_t offset;

    if (!remaining_dst_size)
        return AVERROR_BUFFER_TOO_SMALL;

    while (sei_type && remaining_dst_size != 0) {
        int sei_byte = sei_type > 255 ? 255 : sei_type;
        *dst = sei_byte;

        sei_type -= sei_byte;
        dst++;
        remaining_dst_size--;
    }

    if (!dst_size)
        return AVERROR_BUFFER_TOO_SMALL;

    while (remaining_sei_size && remaining_dst_size != 0) {
        int size_byte = remaining_sei_size > 255 ? 255 : remaining_sei_size;
        *dst = size_byte;

        remaining_sei_size -= size_byte;
        dst++;
        remaining_dst_size--;
    }

    if (remaining_dst_size < sei->size)
        return AVERROR_BUFFER_TOO_SMALL;

    header_bytes = dst - sei_start;

    offset = header_bytes;
    bytes_written = copy_emulation_prev(sei->data,
                                        sei->size,
                                        sei_start,
                                        offset,
                                        dst_size);
    if (bytes_written < 0)
        return AVERROR_BUFFER_TOO_SMALL;

    bytes_written += header_bytes;
    return bytes_written;
}