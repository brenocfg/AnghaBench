#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int character; scalar_t__ direction; } ;
struct TYPE_4__ {unsigned int* buf; TYPE_2__ code128; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code128_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (unsigned int*,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  zassert (int,int,char*,scalar_t__,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char validate_checksum (zbar_decoder_t *dcode)
{
    unsigned idx, sum, i, acc = 0;
    unsigned char check, err;

    code128_decoder_t *dcode128 = &dcode->code128;
    if(dcode128->character < 3)
        return(1);

    /* add in irregularly weighted start character */
    idx = (dcode128->direction) ? dcode128->character - 1 : 0;
    sum = dcode->buf[idx];
    if(sum >= 103)
        sum -= 103;

    /* calculate sum in reverse to avoid multiply operations */
    for(i = dcode128->character - 3; i; i--) {
        zassert(sum < 103, -1, "dir=%x i=%x sum=%x acc=%x %s\n",
                dcode128->direction, i, sum, acc,
                _zbar_decoder_buf_dump(dcode->buf, dcode128->character));
        idx = (dcode128->direction) ? dcode128->character - 1 - i : i;
        acc += dcode->buf[idx];
        if(acc >= 103)
            acc -= 103;
        zassert(acc < 103, -1, "dir=%x i=%x sum=%x acc=%x %s\n",
                dcode128->direction, i, sum, acc,
                _zbar_decoder_buf_dump(dcode->buf, dcode128->character));
        sum += acc;
        if(sum >= 103)
            sum -= 103;
    }

    /* and compare to check character */
    idx = (dcode128->direction) ? 1 : dcode128->character - 2;
    check = dcode->buf[idx];
    dbprintf(2, " chk=%02x(%02x)", sum, check);
    err = (sum != check);
    if(err)
        dbprintf(1, " [checksum error]\n");
    return(err);
}