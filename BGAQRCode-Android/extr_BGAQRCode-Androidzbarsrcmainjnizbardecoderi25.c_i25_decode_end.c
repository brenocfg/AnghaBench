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
struct TYPE_9__ {int width; int direction; int character; } ;
struct TYPE_8__ {int direction; char* buf; int buf_alloc; int buflen; scalar_t__ modifiers; TYPE_2__ i25; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ i25_decoder_t ;

/* Variables and functions */
 int CFG (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_MAX_LEN ; 
 int /*<<< orphan*/  ZBAR_CFG_MIN_LEN ; 
 char ZBAR_I25 ; 
 char ZBAR_NONE ; 
 char ZBAR_PARTIAL ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (char*,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int decode_e (unsigned int,int,int) ; 
 unsigned int get_width (TYPE_1__*,int) ; 
 scalar_t__ i25_acquire_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,char) ; 
 int /*<<< orphan*/  zassert (int,char,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline signed char i25_decode_end (zbar_decoder_t *dcode)
{
    i25_decoder_t *dcode25 = &dcode->i25;

    /* check trailing quiet zone */
    unsigned quiet = get_width(dcode, 0);
    if((quiet && quiet < dcode25->width * 3 / 8) ||
       decode_e(get_width(dcode, 1), dcode25->width, 45) > 2 ||
       decode_e(get_width(dcode, 2), dcode25->width, 45) > 2) {
        dbprintf(3, "      i25: s=%d q=%d [invalid qz]\n",
                 dcode25->width, quiet);
        return(ZBAR_NONE);
    }

    /* check exit condition */
    unsigned char E = decode_e(get_width(dcode, 3), dcode25->width, 45);
    if((!dcode25->direction)
       ? E - 3 > 4
       : (E > 2 ||
          decode_e(get_width(dcode, 4), dcode25->width, 45) > 2))
        return(ZBAR_NONE);

    if(dcode25->character <= 4 &&
       i25_acquire_lock(dcode))
        return(ZBAR_PARTIAL);

    dcode->direction = 1 - 2 * dcode25->direction;
    if(dcode25->direction) {
        /* reverse buffer */
        dbprintf(2, " (rev)");
        int i;
        for(i = 0; i < dcode25->character / 2; i++) {
            unsigned j = dcode25->character - 1 - i;
            char c = dcode->buf[i];
            dcode->buf[i] = dcode->buf[j];
            dcode->buf[j] = c;
        }
    }

    if(dcode25->character < CFG(*dcode25, ZBAR_CFG_MIN_LEN) ||
       (CFG(*dcode25, ZBAR_CFG_MAX_LEN) > 0 &&
        dcode25->character > CFG(*dcode25, ZBAR_CFG_MAX_LEN))) {
        dbprintf(2, " [invalid len]\n");
        release_lock(dcode, ZBAR_I25);
        dcode25->character = -1;
        return(ZBAR_NONE);
    }

    zassert(dcode25->character < dcode->buf_alloc, ZBAR_NONE, "i=%02x %s\n",
            dcode25->character,
            _zbar_decoder_buf_dump(dcode->buf, dcode25->character));
    dcode->buflen = dcode25->character;
    dcode->buf[dcode25->character] = '\0';
    dcode->modifiers = 0;
    dbprintf(2, " [valid end]\n");
    dcode25->character = -1;
    return(ZBAR_I25);
}