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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (unsigned int) ; 
 unsigned int avio_read (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  decode_block (char*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int get_v (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  recover_key (char*,unsigned int) ; 

__attribute__((used)) static uint8_t *read_sb_block(AVIOContext *src, unsigned *size,
                              uint32_t *key, unsigned expected_size)
{
    uint8_t *buf;
    uint8_t ibuf[8], sbuf[8];
    uint32_t k2;
    unsigned n;

    if (avio_read(src, ibuf, 8) < 8)
        return NULL;

    k2 = *key;
    decode_block(ibuf, sbuf, 8, *key, &k2, 0);

    n = get_v(sbuf+2, 6);

    if (sbuf[0] != 'S' || sbuf[1] != 'B' || (expected_size>0 && n != expected_size)) {
        uint32_t tmpkey = recover_key(ibuf, expected_size);
        k2 = tmpkey;
        decode_block(ibuf, sbuf, 8, tmpkey, &k2, 0);
        n = get_v(sbuf+2, 6);
        if (sbuf[0] != 'S' || sbuf[1] != 'B' || expected_size != n)
            return NULL;
        *key = tmpkey;
    }

    if (n < 8)
        return NULL;

    buf = av_malloc(n);
    if (!buf)
        return NULL;

    memcpy(buf, sbuf, 8);

    *size = n;
    n -= 8;

    if (avio_read(src, buf+8, n) < n) {
        av_free(buf);
        return NULL;
    }

    decode_block(buf + 8, buf + 8, n, *key, &k2, 0);

    return buf;
}