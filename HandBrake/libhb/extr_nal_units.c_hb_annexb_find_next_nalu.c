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

/* Variables and functions */

uint8_t* hb_annexb_find_next_nalu(const uint8_t *start, size_t *size)
{
    uint8_t *nal = NULL;
    uint8_t *buf = (uint8_t*)start;
    uint8_t *end = (uint8_t*)start + *size;

    /* Look for an Annex B start code prefix (3-byte sequence == 1) */
    while (end - buf > 3)
    {
        if (!buf[0] && !buf[1] && buf[2] == 1)
        {
            nal = (buf += 3); // NAL unit begins after start code
            break;
        }
        buf++;
    }

    if (nal == NULL)
    {
        *size = 0;
        return NULL;
    }

    /*
     * Start code prefix found, look for the next one to determine the size
     *
     * A 4-byte sequence == 1 is also a start code, so check for a 3-byte
     * sequence == 0 too (start code emulation prevention will prevent such a
     * sequence from occurring outside of a start code prefix)
     */
    while (end - buf > 3)
    {
        if (!buf[0] && !buf[1] && (!buf[2] || buf[2] == 1))
        {
            end = buf;
            break;
        }
        buf++;
    }

    *size = end - nal;
    return  nal;
}