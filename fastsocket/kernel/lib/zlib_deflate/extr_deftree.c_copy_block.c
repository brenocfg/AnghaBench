#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ush ;
typedef  int ulg ;
struct TYPE_5__ {int last_eob_len; int bits_sent; size_t pending; int /*<<< orphan*/ * pending_buf; } ;
typedef  TYPE_1__ deflate_state ;

/* Variables and functions */
 int /*<<< orphan*/  bi_windup (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  put_short (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_block(
	deflate_state *s,
	char    *buf,     /* the input data */
	unsigned len,     /* its length */
	int      header   /* true if block header must be written */
)
{
    bi_windup(s);        /* align on byte boundary */
    s->last_eob_len = 8; /* enough lookahead for inflate */

    if (header) {
        put_short(s, (ush)len);   
        put_short(s, (ush)~len);
#ifdef DEBUG_ZLIB
        s->bits_sent += 2*16;
#endif
    }
#ifdef DEBUG_ZLIB
    s->bits_sent += (ulg)len<<3;
#endif
    /* bundle up the put_byte(s, *buf++) calls */
    memcpy(&s->pending_buf[s->pending], buf, len);
    s->pending += len;
}