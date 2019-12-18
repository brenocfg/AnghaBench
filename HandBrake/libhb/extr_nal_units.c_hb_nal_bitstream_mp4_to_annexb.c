#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ hb_buffer_t ;

/* Variables and functions */
 TYPE_1__* hb_buffer_init (size_t) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_log (char*,int,size_t) ; 
 scalar_t__ hb_nal_unit_write_annexb (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  mp4_nal_unit_length (int*,int const,size_t*) ; 

hb_buffer_t* hb_nal_bitstream_mp4_to_annexb(const uint8_t *data,
                                            const size_t size,
                                            const uint8_t nal_length_size)
{
    hb_buffer_t *out;
    uint8_t *buf, *end;
    size_t out_size, nal_size;

    out_size = 0;
    buf      = (uint8_t*)data;
    end      = (uint8_t*)data + size;

    while (end - buf > nal_length_size)
    {
        buf += mp4_nal_unit_length(buf, nal_length_size, &nal_size);
        if (end - buf < nal_size)
        {
            hb_log("hb_nal_bitstream_mp4_to_annexb: truncated bitstream"
                   " (remaining: %lu, expected: %lu)", end - buf, nal_size);
            return NULL;
        }

        out_size += hb_nal_unit_write_annexb(NULL, buf, nal_size);
        buf      += nal_size;
    }

    out = hb_buffer_init(out_size);
    if (out == NULL)
    {
        hb_error("hb_nal_bitstream_mp4_to_annexb: hb_buffer_init failed");
        return NULL;
    }

    out_size = 0;
    buf      = (uint8_t*)data;
    end      = (uint8_t*)data + size;

    while (end - buf > nal_length_size)
    {
        buf      += mp4_nal_unit_length(buf, nal_length_size, &nal_size);
        out_size += hb_nal_unit_write_annexb(out->data + out_size, buf, nal_size);
        buf      += nal_size;
    }

    return out;
}