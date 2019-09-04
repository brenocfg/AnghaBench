#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_decoder_t ;

/* Variables and functions */
 unsigned int get_width (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline unsigned decode_sort3 (zbar_decoder_t *dcode,
                                     int i0)
{
    unsigned w0 = get_width(dcode, i0);
    unsigned w2 = get_width(dcode, i0 + 2);
    unsigned w4 = get_width(dcode, i0 + 4);
    if(w0 < w2) {
        if(w2 < w4)
            return((i0 << 8) | ((i0 + 2) << 4) | (i0 + 4));
        if(w0 < w4)
            return((i0 << 8) | ((i0 + 4) << 4) | (i0 + 2));
        return(((i0 + 4) << 8) | (i0 << 4) | (i0 + 2));
    }
    if(w4 < w2)
        return(((i0 + 4) << 8) | ((i0 + 2) << 4) | i0);
    if(w0 < w4)
        return(((i0 + 2) << 8) | (i0 << 4) | (i0 + 4));
    return(((i0 + 2) << 8) | ((i0 + 4) << 4) | i0);
}