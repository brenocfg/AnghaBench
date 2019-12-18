#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int s32 ;
struct TYPE_7__ {TYPE_1__* imghead; } ;
struct TYPE_6__ {int ntextures; scalar_t__ texdesc; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ TPLImgHeader ;
typedef  TYPE_2__ TPLFile ;
typedef  TYPE_3__ TPLDescHeader ;

/* Variables and functions */

s32 TPL_GetTextureInfo(TPLFile *tdf,s32 id,u32 *fmt,u16 *width,u16 *height)
{
	TPLDescHeader *deschead = NULL;
	TPLImgHeader *imghead = NULL;

	if(!tdf) return -1;
	if(id<0 || id>=tdf->ntextures) return -1;

	deschead = (TPLDescHeader*)tdf->texdesc;
	if(!deschead) return -1;

	imghead = deschead[id].imghead;
	if(!imghead) return -1;

	if(fmt) *fmt = imghead->fmt;
	if(width) *width = imghead->width;
	if(height) *height = imghead->height;

	return 0;
}