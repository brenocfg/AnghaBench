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
struct TYPE_3__ {unsigned char* buf; } ;
typedef  TYPE_1__ ean_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (void*,int) ; 
 int /*<<< orphan*/  zassert (int,char,char*,unsigned char,unsigned char,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char isbn10_calc_checksum (ean_decoder_t *ean)
{
    unsigned int chk = 0;
    unsigned char w;
    for(w = 10; w > 1; w--) {
        unsigned char d = ean->buf[13 - w];
        zassert(d < 10, '?', "w=%x d=%x chk=%x %s\n", w, d, chk,
                _zbar_decoder_buf_dump((void*)ean->buf, 18));
        chk += d * w;
    }
    chk = chk % 11;
    if(!chk)
        return('0');
    chk = 11 - chk;
    if(chk < 10)
        return(chk + '0');
    return('X');
}