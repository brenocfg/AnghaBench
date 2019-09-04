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
struct TYPE_3__ {int y; int /*<<< orphan*/ * b3; int /*<<< orphan*/ * b2; int /*<<< orphan*/ * b1; int /*<<< orphan*/ * b0; } ;
typedef  int /*<<< orphan*/  IDWTELEM ;
typedef  TYPE_1__ DWTCompose ;

/* Variables and functions */
 int avpriv_mirror (int,int) ; 
 int /*<<< orphan*/  ff_snow_horizontal_compose97i (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose97iH0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose97iH1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose97iL0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose97iL1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void spatial_compose97i_dy(DWTCompose *cs, IDWTELEM *buffer,
                                  IDWTELEM *temp, int width, int height,
                                  int stride)
{
    int y        = cs->y;
    IDWTELEM *b0 = cs->b0;
    IDWTELEM *b1 = cs->b1;
    IDWTELEM *b2 = cs->b2;
    IDWTELEM *b3 = cs->b3;
    IDWTELEM *b4 = buffer + avpriv_mirror(y + 3, height - 1) * stride;
    IDWTELEM *b5 = buffer + avpriv_mirror(y + 4, height - 1) * stride;

    if (y + 3 < (unsigned)height)
        vertical_compose97iL1(b3, b4, b5, width);
    if (y + 2 < (unsigned)height)
        vertical_compose97iH1(b2, b3, b4, width);
    if (y + 1 < (unsigned)height)
        vertical_compose97iL0(b1, b2, b3, width);
    if (y + 0 < (unsigned)height)
        vertical_compose97iH0(b0, b1, b2, width);

    if (y - 1 < (unsigned)height)
        ff_snow_horizontal_compose97i(b0, temp, width);
    if (y + 0 < (unsigned)height)
        ff_snow_horizontal_compose97i(b1, temp, width);

    cs->b0  = b2;
    cs->b1  = b3;
    cs->b2  = b4;
    cs->b3  = b5;
    cs->y  += 2;
}