#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bPicEntry; } ;
struct TYPE_4__ {TYPE_3__* RefPicList; } ;
typedef  TYPE_1__ DXVA_PicParams_HEVC ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 

__attribute__((used)) static int get_refpic_index(const DXVA_PicParams_HEVC *pp, int surface_index)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(pp->RefPicList); i++) {
        if ((pp->RefPicList[i].bPicEntry & 0x7f) == surface_index)
          return i;
    }
    return 0xff;
}