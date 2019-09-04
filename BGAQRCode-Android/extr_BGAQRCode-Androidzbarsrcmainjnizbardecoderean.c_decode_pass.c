#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int zbar_symbol_type_t ;
struct TYPE_21__ {int direction; unsigned int s4; int /*<<< orphan*/  ean8_config; } ;
struct TYPE_19__ {TYPE_5__ ean; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_20__ {unsigned char state; int* raw; unsigned int width; } ;
typedef  TYPE_2__ ean_pass_t ;

/* Variables and functions */
 int STATE_ADDON ; 
 unsigned char STATE_IDX ; 
 int STATE_REV ; 
 scalar_t__ TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ENABLE ; 
 int ZBAR_NONE ; 
 scalar_t__ ZBAR_SPACE ; 
 int /*<<< orphan*/  aux_end (TYPE_1__*,unsigned char) ; 
 scalar_t__ aux_mid (TYPE_1__*) ; 
 int aux_start (TYPE_1__*) ; 
 unsigned int calc_s (TYPE_1__*,int,int) ; 
 unsigned int check_width (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 char decode4 (TYPE_1__*) ; 
 int* digits ; 
 int ean_part_end2 (TYPE_5__*,TYPE_2__*) ; 
 int ean_part_end4 (TYPE_2__*,unsigned char) ; 
 int ean_part_end5 (TYPE_5__*,TYPE_2__*) ; 
 int ean_part_end7 (TYPE_5__*,TYPE_2__*,unsigned char) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 unsigned int get_width (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zbar_symbol_type_t decode_pass (zbar_decoder_t *dcode,
                                              ean_pass_t *pass)
{
    unsigned char idx, fwd;
    pass->state++;
    idx = pass->state & STATE_IDX;
    fwd = pass->state & 1;

    if(get_color(dcode) == ZBAR_SPACE) {
        if(pass->state & STATE_ADDON) {
            dbprintf(2, " i=%d", idx);
            if(idx == 0x09 || idx == 0x21) {
                unsigned qz = get_width(dcode, 0);
                unsigned s = calc_s(dcode, 1, 4);
                zbar_symbol_type_t part = !qz || (qz >= s * 3 / 4);
                if(part && idx == 0x09)
                    part = ean_part_end2(&dcode->ean, pass);
                else if(part)
                    part = ean_part_end5(&dcode->ean, pass);

                if(part || idx == 0x21) {
                    dcode->ean.direction = 0;
                    pass->state = -1;
                    return(part);
                }
            }
            if((idx & 7) == 1) {
                dbprintf(2, " +");
                pass->state += 2;
                idx += 2;
            }
        }
        else if((idx == 0x10 || idx == 0x11) &&
                TEST_CFG(dcode->ean.ean8_config, ZBAR_CFG_ENABLE) &&
                !aux_end(dcode, fwd)) {
            dbprintf(2, " fwd=%x", fwd);
            zbar_symbol_type_t part = ean_part_end4(pass, fwd);
            if(part)
                dcode->ean.direction = (pass->state & STATE_REV) != 0;
            pass->state = -1;
            return(part);
        }
	else if((idx == 0x18 || idx == 0x19)) {
	  zbar_symbol_type_t part = ZBAR_NONE;
	  dbprintf(2, " fwd=%x", fwd);
	  if(!aux_end(dcode, fwd) && pass->raw[5] != 0xff)
	    part = ean_part_end7(&dcode->ean, pass, fwd);
	  if(part)
	    dcode->ean.direction = (pass->state & STATE_REV) != 0;
	  pass->state = -1;
	  return(part);
        }
    }

    if(pass->state & STATE_ADDON)
        idx >>= 1;

    if(!(idx & 0x03) && idx <= 0x14) {
        signed char code = -1;
        unsigned w = pass->width;
        if(!dcode->ean.s4)
            return(0);
        /* validate guard bars before decoding first char of symbol */
        if(!pass->state) {
            pass->state = aux_start(dcode);
            pass->width = dcode->ean.s4;
            if(pass->state < 0)
                return(0);
            idx = pass->state & STATE_IDX;
        }
        else {
            w = check_width(w, dcode->ean.s4);
            if(w)
                pass->width = (pass->width + dcode->ean.s4 * 3) / 4;
        }

        if(w)
            code = decode4(dcode);
        else
            dbprintf(2, " [bad width]");

        if((code < 0 && idx != 0x10) || 
           (idx > 0 && (pass->state & STATE_ADDON) && aux_mid(dcode)))
            pass->state = -1;
        else if(code < 0)
            pass->raw[5] = 0xff;
        else {
            dbprintf(2, "\n        raw[%x]=%02x =>", idx >> 2,
                     digits[(unsigned char)code]);
            pass->raw[(idx >> 2) + 1] = digits[(unsigned char)code];
            dbprintf(2, " raw=%d%d%d%d%d%d%d",
                     pass->raw[0] & 0xf, pass->raw[1] & 0xf,
                     pass->raw[2] & 0xf, pass->raw[3] & 0xf,
                     pass->raw[4] & 0xf, pass->raw[5] & 0xf,
                     pass->raw[6] & 0xf);
        }
    }
    return(0);
}