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
struct TYPE_4__ {scalar_t__ pic_width; scalar_t__ pic_height; scalar_t__ chroma_width; scalar_t__ chroma_height; scalar_t__ tile_width; scalar_t__ tile_height; scalar_t__ luma_bands; scalar_t__ chroma_bands; } ;
typedef  TYPE_1__ IVIPicConfig ;

/* Variables and functions */

__attribute__((used)) static inline int ivi_pic_config_cmp(IVIPicConfig *str1, IVIPicConfig *str2)
{
    return str1->pic_width    != str2->pic_width    || str1->pic_height    != str2->pic_height    ||
           str1->chroma_width != str2->chroma_width || str1->chroma_height != str2->chroma_height ||
           str1->tile_width   != str2->tile_width   || str1->tile_height   != str2->tile_height   ||
           str1->luma_bands   != str2->luma_bands   || str1->chroma_bands  != str2->chroma_bands;
}