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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (unsigned int) ; 
 unsigned int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  decode_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int*,int) ; 
 unsigned int get_v (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t *read_vblock(AVIOContext *src, uint32_t *size,
                            uint32_t key, uint32_t *k2, int align)
{
    uint8_t tmp[4];
    uint8_t *buf;
    unsigned n;

    if (avio_read(src, tmp, 4) != 4)
        return NULL;

    decode_block(tmp, tmp, 4, key, k2, align);

    n = get_v(tmp, 4);
    if (n < 4)
        return NULL;

    buf = av_malloc(n);
    if (!buf)
        return NULL;

    *size = n;
    n -= 4;

    memcpy(buf, tmp, 4);

    if (avio_read(src, buf + 4, n) == n) {
        decode_block(buf + 4, buf + 4, n, key, k2, align);
    } else {
        av_free(buf);
        buf = NULL;
    }

    return buf;
}