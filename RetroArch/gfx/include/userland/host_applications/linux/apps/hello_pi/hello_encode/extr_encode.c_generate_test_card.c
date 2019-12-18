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
struct TYPE_6__ {int nStride; int nSliceHeight; int nFrameHeight; int nFrameWidth; } ;
struct TYPE_5__ {TYPE_2__ video; } ;
struct TYPE_7__ {TYPE_1__ format; } ;
typedef  TYPE_2__ OMX_VIDEO_PORTDEFINITIONTYPE ;
typedef  int OMX_U32 ;
typedef  TYPE_3__ OMX_PARAM_PORTDEFINITIONTYPE ;

/* Variables and functions */

__attribute__((used)) static int
generate_test_card(void *buf, OMX_U32 * filledLen, int frame, OMX_PARAM_PORTDEFINITIONTYPE *def)
{
   int i, j;
   OMX_VIDEO_PORTDEFINITIONTYPE *vid = &def->format.video;
   char *y = buf;
   char *u = y + vid->nStride * vid->nSliceHeight;
   char *v = u + (vid->nStride >> 1) * (vid->nSliceHeight >> 1);

   for (j = 0; j < vid->nFrameHeight / 2; j++) {
      char *py = y + 2 * j * vid->nStride;
      char *pu = u + j * (vid->nStride >> 1);
      char *pv = v + j * (vid->nStride >> 1);
      for (i = 0; i < vid->nFrameWidth / 2; i++) {
         int z = (((i + frame) >> 4) ^ ((j + frame) >> 4)) & 15;
         py[0] = py[1] = py[vid->nStride] = py[vid->nStride + 1] = 0x80 + z * 0x8;
         pu[0] = 0x00 + z * 0x10;
         pv[0] = 0x80 + z * 0x30;
         py += 2;
         pu++;
         pv++;
      }
   }
   *filledLen = (vid->nStride * vid->nSliceHeight * 3) >> 1;
   return 1;
}