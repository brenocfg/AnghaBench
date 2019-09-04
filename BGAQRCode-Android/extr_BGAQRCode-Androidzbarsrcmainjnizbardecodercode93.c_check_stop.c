#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_9__ {unsigned int character; scalar_t__ direction; } ;
struct TYPE_8__ {unsigned int s6; TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 unsigned int CFG (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_MAX_LEN ; 
 int /*<<< orphan*/  ZBAR_CFG_MIN_LEN ; 
 int /*<<< orphan*/  ZBAR_CODE93 ; 
 int /*<<< orphan*/  decode_abort (TYPE_1__*,char*) ; 
 scalar_t__ decode_e (int /*<<< orphan*/ ,unsigned int,int) ; 
 unsigned int get_width (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pair_width (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zbar_symbol_type_t
check_stop (zbar_decoder_t *dcode)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    unsigned n = dcode93->character, s = dcode->s6;
    int max_len = CFG(*dcode93, ZBAR_CFG_MAX_LEN);
    if(n < 2 ||
       n < CFG(*dcode93, ZBAR_CFG_MIN_LEN) ||
       (max_len && n > max_len))
        return(decode_abort(dcode, "invalid len"));

    if(dcode93->direction) {
        unsigned qz = get_width(dcode, 0);
        if(qz && qz < (s * 3) / 4)
            return(decode_abort(dcode, "invalid qz"));
    }
    else if(decode_e(pair_width(dcode, 0), s, 9))
        /* FIXME forward-trailing QZ check */
        return(decode_abort(dcode, "invalid stop"));

    return(ZBAR_CODE93);
}