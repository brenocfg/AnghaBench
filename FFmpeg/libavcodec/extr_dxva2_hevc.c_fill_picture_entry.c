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
struct TYPE_3__ {unsigned int bPicEntry; } ;
typedef  TYPE_1__ DXVA_PicEntry_HEVC ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static void fill_picture_entry(DXVA_PicEntry_HEVC *pic,
                               unsigned index, unsigned flag)
{
    av_assert0((index & 0x7f) == index && (flag & 0x01) == flag);
    pic->bPicEntry = index | (flag << 7);
}