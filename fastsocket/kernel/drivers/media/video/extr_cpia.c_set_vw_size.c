#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; int x; int y; } ;
struct TYPE_9__ {int colStart; int rowStart; int colEnd; int rowEnd; } ;
struct TYPE_8__ {int videoSize; } ;
struct TYPE_10__ {int streamStartLine; TYPE_4__ roi; TYPE_3__ format; } ;
struct TYPE_7__ {int width; int height; } ;
struct cam_data {int video_size; TYPE_1__ vc; TYPE_5__ params; TYPE_2__ vw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,int) ; 
#define  VIDEOSIZE_128_96 139 
#define  VIDEOSIZE_192_144 138 
#define  VIDEOSIZE_224_168 137 
#define  VIDEOSIZE_256_192 136 
#define  VIDEOSIZE_288_216 135 
#define  VIDEOSIZE_48_48 134 
#define  VIDEOSIZE_64_48 133 
#define  VIDEOSIZE_88_72 132 
#define  VIDEOSIZE_CIF 131 
#define  VIDEOSIZE_QCIF 130 
#define  VIDEOSIZE_QSIF 129 
#define  VIDEOSIZE_SIF 128 

__attribute__((used)) static void set_vw_size(struct cam_data *cam)
{
	/* the col/row/start/end values are the result of simple math    */
	/* study the SetROI-command in cpia developers guide p 2-22      */
	/* streamStartLine is set to the recommended value in the cpia   */
	/*  developers guide p 3-37                                      */
	switch(cam->video_size) {
	case VIDEOSIZE_CIF:
		cam->vw.width = 352;
		cam->vw.height = 288;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=0;
		cam->params.roi.rowStart=0;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_SIF:
		cam->vw.width = 320;
		cam->vw.height = 240;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=2;
		cam->params.roi.rowStart=6;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_288_216:
		cam->vw.width = 288;
		cam->vw.height = 216;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=4;
		cam->params.roi.rowStart=9;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_256_192:
		cam->vw.width = 256;
		cam->vw.height = 192;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=6;
		cam->params.roi.rowStart=12;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_224_168:
		cam->vw.width = 224;
		cam->vw.height = 168;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=8;
		cam->params.roi.rowStart=15;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_192_144:
		cam->vw.width = 192;
		cam->vw.height = 144;
		cam->params.format.videoSize=VIDEOSIZE_CIF;
		cam->params.roi.colStart=10;
		cam->params.roi.rowStart=18;
		cam->params.streamStartLine = 120;
		break;
	case VIDEOSIZE_QCIF:
		cam->vw.width = 176;
		cam->vw.height = 144;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=0;
		cam->params.roi.rowStart=0;
		cam->params.streamStartLine = 60;
		break;
	case VIDEOSIZE_QSIF:
		cam->vw.width = 160;
		cam->vw.height = 120;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=1;
		cam->params.roi.rowStart=3;
		cam->params.streamStartLine = 60;
		break;
	case VIDEOSIZE_128_96:
		cam->vw.width = 128;
		cam->vw.height = 96;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=3;
		cam->params.roi.rowStart=6;
		cam->params.streamStartLine = 60;
		break;
	case VIDEOSIZE_88_72:
		cam->vw.width = 88;
		cam->vw.height = 72;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=5;
		cam->params.roi.rowStart=9;
		cam->params.streamStartLine = 60;
		break;
	case VIDEOSIZE_64_48:
		cam->vw.width = 64;
		cam->vw.height = 48;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=7;
		cam->params.roi.rowStart=12;
		cam->params.streamStartLine = 60;
		break;
	case VIDEOSIZE_48_48:
		cam->vw.width = 48;
		cam->vw.height = 48;
		cam->params.format.videoSize=VIDEOSIZE_QCIF;
		cam->params.roi.colStart=8;
		cam->params.roi.rowStart=6;
		cam->params.streamStartLine = 60;
		break;
	default:
		LOG("bad videosize value: %d\n", cam->video_size);
		return;
	}

	if(cam->vc.width == 0)
		cam->vc.width = cam->vw.width;
	if(cam->vc.height == 0)
		cam->vc.height = cam->vw.height;

	cam->params.roi.colStart += cam->vc.x >> 3;
	cam->params.roi.colEnd = cam->params.roi.colStart +
				 (cam->vc.width >> 3);
	cam->params.roi.rowStart += cam->vc.y >> 2;
	cam->params.roi.rowEnd = cam->params.roi.rowStart +
				 (cam->vc.height >> 2);

	return;
}