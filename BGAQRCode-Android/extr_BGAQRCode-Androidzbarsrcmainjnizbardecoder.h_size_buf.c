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
struct TYPE_3__ {unsigned int buf_alloc; unsigned char* buf; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 unsigned int BUFFER_INCR ; 
 unsigned int BUFFER_MAX ; 
 unsigned int BUFFER_MIN ; 
 unsigned char* realloc (unsigned char*,unsigned int) ; 

__attribute__((used)) static inline char size_buf (zbar_decoder_t *dcode,
                             unsigned len)
{
    unsigned char *buf;
    if(len <= BUFFER_MIN)
        return(0);
    if(len < dcode->buf_alloc)
        /* FIXME size reduction heuristic? */
        return(0);
    if(len > BUFFER_MAX)
        return(1);
    if(len < dcode->buf_alloc + BUFFER_INCR) {
        len = dcode->buf_alloc + BUFFER_INCR;
        if(len > BUFFER_MAX)
            len = BUFFER_MAX;
    }
    buf = realloc(dcode->buf, len);
    if(!buf)
        return(1);
    dcode->buf = buf;
    dcode->buf_alloc = len;
    return(0);
}