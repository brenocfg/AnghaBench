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
 unsigned int UINT_MAX ; 
 unsigned int get_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zassert (int,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static inline unsigned decode_sortn (zbar_decoder_t *dcode,
                                     int n,
                                     int i0)
{
    unsigned mask = 0, sort = 0;
    int i;
    for(i = n - 1; i >= 0; i--) {
        unsigned wmin = UINT_MAX;
        int jmin = -1, j;
        for(j = n - 1; j >= 0; j--) {
            if((mask >> j) & 1)
                continue;
            unsigned w = get_width(dcode, i0 + j * 2);
            if(wmin >= w) {
                wmin = w;
                jmin = j;
            }
        }
        zassert(jmin >= 0, 0, "sortn(%d,%d) jmin=%d",
                n, i0, jmin);
        sort <<= 4;
        mask |= 1 << jmin;
        sort |= i0 + jmin * 2;
    }
    return(sort);
}