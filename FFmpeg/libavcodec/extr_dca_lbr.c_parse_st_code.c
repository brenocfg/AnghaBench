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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 unsigned int FF_ARRAY_ELEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_dca_st_coeff ; 
 int /*<<< orphan*/  ff_dca_vlc_st_grid ; 
 int parse_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_st_code(GetBitContext *s, int min_v)
{
    unsigned int v = parse_vlc(s, &ff_dca_vlc_st_grid, 2) + min_v;

    if (v & 1)
        v = 16 + (v >> 1);
    else
        v = 16 - (v >> 1);

    if (v >= FF_ARRAY_ELEMS(ff_dca_st_coeff))
        v = 16;
    return v;
}