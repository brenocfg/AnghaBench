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
 size_t SIZE_MAX ; 
 int* av_malloc (size_t) ; 

__attribute__((used)) static uint8_t *iso88591_to_utf8(const uint8_t *in, size_t size_in)
{
    size_t extra = 0, i;
    uint8_t *out, *q;

    for (i = 0; i < size_in; i++)
        extra += in[i] >= 0x80;
    if (size_in == SIZE_MAX || extra > SIZE_MAX - size_in - 1)
        return NULL;
    q = out = av_malloc(size_in + extra + 1);
    if (!out)
        return NULL;
    for (i = 0; i < size_in; i++) {
        if (in[i] >= 0x80) {
            *(q++) = 0xC0 | (in[i] >> 6);
            *(q++) = 0x80 | (in[i] & 0x3F);
        } else {
            *(q++) = in[i];
        }
    }
    *(q++) = 0;
    return out;
}