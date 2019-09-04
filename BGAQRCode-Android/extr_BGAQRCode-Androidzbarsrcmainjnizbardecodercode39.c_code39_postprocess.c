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
struct TYPE_5__ {int direction; int character; } ;
struct TYPE_4__ {int direction; char* buf; int buf_alloc; int buflen; scalar_t__ modifiers; TYPE_2__ code39; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code39_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (int*,int) ; 
 char* code39_characters ; 
 int /*<<< orphan*/  dbprintf (int,char*) ; 
 int /*<<< orphan*/  zassert (int,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int code39_postprocess (zbar_decoder_t *dcode)
{
    code39_decoder_t *dcode39 = &dcode->code39;
    dcode->direction = 1 - 2 * dcode39->direction;
    int i;
    if(dcode39->direction) {
        /* reverse buffer */
        dbprintf(2, " (rev)");
        for(i = 0; i < dcode39->character / 2; i++) {
            unsigned j = dcode39->character - 1 - i;
            char code = dcode->buf[i];
            dcode->buf[i] = dcode->buf[j];
            dcode->buf[j] = code;
        }
    }
    for(i = 0; i < dcode39->character; i++)
        dcode->buf[i] = ((dcode->buf[i] < 0x2b)
                         ? code39_characters[(unsigned)dcode->buf[i]]
                         : '?');
    zassert(i < dcode->buf_alloc, -1, "i=%02x %s\n", i,
            _zbar_decoder_buf_dump(dcode->buf, dcode39->character));
    dcode->buflen = i;
    dcode->buf[i] = '\0';
    dcode->modifiers = 0;
    return(0);
}