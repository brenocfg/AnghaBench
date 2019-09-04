#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* raw; } ;
typedef  TYPE_1__ ean_pass_t ;
struct TYPE_6__ {int* buf; } ;
typedef  TYPE_2__ ean_decoder_t ;

/* Variables and functions */

__attribute__((used)) static inline void ean_expand_upce (ean_decoder_t *ean,
                                    ean_pass_t *pass)
{
    int i = 0;
    unsigned char decode;
    /* parity encoded digit is checksum */
    ean->buf[12] = pass->raw[i++];

    decode = pass->raw[6] & 0xf;
    ean->buf[0] = 0;
    ean->buf[1] = 0;
    ean->buf[2] = pass->raw[i++] & 0xf;
    ean->buf[3] = pass->raw[i++] & 0xf;
    ean->buf[4] = (decode < 3) ? decode : pass->raw[i++] & 0xf;
    ean->buf[5] = (decode < 4) ? 0 : pass->raw[i++] & 0xf;
    ean->buf[6] = (decode < 5) ? 0 : pass->raw[i++] & 0xf;
    ean->buf[7] = 0;
    ean->buf[8] = 0;
    ean->buf[9] = (decode < 3) ? pass->raw[i++] & 0xf : 0;
    ean->buf[10] = (decode < 4) ? pass->raw[i++] & 0xf : 0;
    ean->buf[11] = (decode < 5) ? pass->raw[i] & 0xf : decode;
}