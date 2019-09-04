#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  sw_format; } ;
struct TYPE_8__ {int RowPitch; scalar_t__ pData; } ;
struct TYPE_7__ {int /*<<< orphan*/  Height; } ;
typedef  TYPE_1__ D3D11_TEXTURE2D_DESC ;
typedef  TYPE_2__ D3D11_MAPPED_SUBRESOURCE ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_fill_pointers (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void fill_texture_ptrs(uint8_t *data[4], int linesize[4],
                              AVHWFramesContext *ctx,
                              D3D11_TEXTURE2D_DESC *desc,
                              D3D11_MAPPED_SUBRESOURCE *map)
{
    int i;

    for (i = 0; i < 4; i++)
        linesize[i] = map->RowPitch;

    av_image_fill_pointers(data, ctx->sw_format, desc->Height,
                           (uint8_t*)map->pData, linesize);
}