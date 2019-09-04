#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int s6; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbprintf (int,char*,int) ; 
 unsigned int decode_e (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  pair_width (TYPE_1__*,int) ; 

__attribute__((used)) static inline int
encode6 (zbar_decoder_t *dcode)
{
    /* build edge signature of character */
    unsigned s = dcode->s6;
    int sig = 0, i;

    dbprintf(2, " s=%d ", s);
    if(s < 9)
        return(-1);

    for(i = 6; --i > 0; ) {
        unsigned c = decode_e(pair_width(dcode, i), s, 9);
        if(c > 3)
            return(-1);
        sig = (sig << 2) | c;
        dbprintf(2, "%d", c);
    }
    dbprintf(2, " sig=%03x", sig);

    return(sig);
}