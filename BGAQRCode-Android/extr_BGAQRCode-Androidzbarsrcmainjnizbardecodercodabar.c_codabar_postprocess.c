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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_6__ {int direction; int character; char* buf; int /*<<< orphan*/  config; } ;
struct TYPE_5__ {int direction; char* buf; int buflen; scalar_t__ modifiers; TYPE_2__ codabar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ codabar_decoder_t ;

/* Variables and functions */
 int NIBUF ; 
 scalar_t__ TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_ADD_CHECK ; 
 int /*<<< orphan*/  ZBAR_CFG_EMIT_CHECK ; 
 int /*<<< orphan*/  ZBAR_CODABAR ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 char* codabar_characters ; 
 scalar_t__ codabar_checksum (TYPE_1__*,int) ; 

__attribute__((used)) static inline zbar_symbol_type_t
codabar_postprocess (zbar_decoder_t *dcode)
{
    codabar_decoder_t *codabar = &dcode->codabar;
    int dir = codabar->direction;
    dcode->direction = 1 - 2 * dir;
    int i, n = codabar->character;
    for(i = 0; i < NIBUF; i++)
        dcode->buf[i] = codabar->buf[i];
    if(dir)
        /* reverse buffer */
        for(i = 0; i < n / 2; i++) {
            unsigned j = n - 1 - i;
            char code = dcode->buf[i];
            dcode->buf[i] = dcode->buf[j];
            dcode->buf[j] = code;
        }

    if(TEST_CFG(codabar->config, ZBAR_CFG_ADD_CHECK)) {
        /* validate checksum */
        if(codabar_checksum(dcode, n))
            return(ZBAR_NONE);
        if(!TEST_CFG(codabar->config, ZBAR_CFG_EMIT_CHECK)) {
            dcode->buf[n - 2] = dcode->buf[n - 1];
            n--;
        }
    }

    for(i = 0; i < n; i++) {
        unsigned c = dcode->buf[i];
        dcode->buf[i] = ((c < 0x14)
                         ? codabar_characters[c]
                         : '?');
    }
    dcode->buflen = i;
    dcode->buf[i] = '\0';
    dcode->modifiers = 0;

    codabar->character = -1;
    return(ZBAR_CODABAR);
}