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
struct TYPE_5__ {unsigned int character; scalar_t__ direction; } ;
struct TYPE_4__ {unsigned int* buf; TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,unsigned int,unsigned int) ; 
 unsigned int plusmod47 (unsigned int,unsigned int) ; 

__attribute__((used)) static inline int
validate_checksums (zbar_decoder_t *dcode)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    unsigned d, i, n = dcode93->character;
    unsigned sum_c = 0, acc_c = 0, i_c = (n - 2) % 20;
    unsigned sum_k = 0, acc_k = 0, i_k = (n - 1) % 15;

    for(i = 0; i < n - 2; i++) {
        d = dcode->buf[(dcode93->direction) ? n - 1 - i : i];

        if(!i_c--) {
            acc_c = 0;
            i_c = 19;
        }
        acc_c = plusmod47(acc_c, d);
        sum_c = plusmod47(sum_c, acc_c);

        if(!i_k--) {
            acc_k = 0;
            i_k = 14;
        }
        acc_k = plusmod47(acc_k, d);
        sum_k = plusmod47(sum_k, acc_k);
    }

    d = dcode->buf[(dcode93->direction) ? 1 : n - 2];
    dbprintf(2, " C=%02x?=%02x", d, sum_c);
    if(d != sum_c)
        return(1);

    acc_k = plusmod47(acc_k, sum_c);
    sum_k = plusmod47(sum_k, acc_k);
    d = dcode->buf[(dcode93->direction) ? 0 : n - 1];
    dbprintf(2, " K=%02x?=%02x", d, sum_k);
    if(d != sum_k)
        return(1);

    return(0);
}