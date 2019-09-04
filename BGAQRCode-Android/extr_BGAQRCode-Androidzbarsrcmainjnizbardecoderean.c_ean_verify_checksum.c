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
struct TYPE_4__ {unsigned char* buf; } ;
typedef  TYPE_1__ ean_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (void*,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsprintbuf (TYPE_1__*) ; 
 int /*<<< orphan*/  zassert (int,int,char*,int,unsigned char,unsigned char,...) ; 

__attribute__((used)) static inline signed char ean_verify_checksum (ean_decoder_t *ean,
                                               int n)
{
    unsigned char chk = 0;
    unsigned char i, d;
    for(i = 0; i < n; i++) {
        unsigned char d = ean->buf[i];
        zassert(d < 10, -1, "i=%x d=%x chk=%x %s\n", i, d, chk,
                _zbar_decoder_buf_dump((void*)ean->buf, 18));
        chk += d;
        if((i ^ n) & 1) {
            chk += d << 1;
            if(chk >= 20)
                chk -= 20;
        }
        if(chk >= 10)
            chk -= 10;
    }
    zassert(chk < 10, -1, "chk=%x n=%x %s", chk, n,
            _zbar_decoder_buf_dump((void*)ean->buf, 18));
    if(chk)
        chk = 10 - chk;
    d = ean->buf[n];
    zassert(d < 10, -1, "n=%x d=%x chk=%x %s\n", n, d, chk,
            _zbar_decoder_buf_dump((void*)ean->buf, 18));
    if(chk != d) {
        dbprintf(1, "\nchecksum mismatch %d != %d (%s)\n",
                 chk, d, dsprintbuf(ean));
        return(-1);
    }
    return(0);
}