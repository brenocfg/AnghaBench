#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int* data; int count; } ;
struct TYPE_8__ {int systemState; int grabState; int streamState; int fatalError; int cmdError; int debugFlags; int vpStatus; int errorCode; } ;
struct TYPE_7__ {int yThreshold; int uvThreshold; } ;
struct TYPE_11__ {int colStart; int colEnd; int rowStart; int rowEnd; } ;
struct TYPE_12__ {TYPE_2__ status; TYPE_1__ yuvThreshold; TYPE_5__ roi; } ;
struct TYPE_10__ {int palette; } ;
struct cam_data {int* raw_image; int fps; TYPE_3__ decompressed_frame; int /*<<< orphan*/  mmap_kludge; int /*<<< orphan*/  param_lock; TYPE_6__ params; TYPE_4__ vp; } ;

/* Variables and functions */
 int COMPRESSED ; 
 int CPIA_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int DECIMATION_ENAB ; 
 int EOI ; 
 int EOL ; 
 scalar_t__ FRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  LOG (char*,...) ; 
 int MAGIC_0 ; 
 int MAGIC_1 ; 
 int NOT_COMPRESSED ; 
 int NO_DECIMATION ; 
 int SUBSAMPLE_420 ; 
 int SUBSAMPLE_422 ; 
 int VIDEOSIZE_CIF ; 
 int VIDEOSIZE_QCIF ; 
 int YUVORDER_UYVY ; 
 int YUVORDER_YUYV ; 
 int /*<<< orphan*/  convert420 (int*,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int skipcount (int,int) ; 
 int /*<<< orphan*/  yuvconvert (int*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_picture(struct cam_data *cam, int size)
{
	u8 *obuf, *ibuf, *end_obuf;
	int ll, in_uyvy, compressed, decimation, even_line, origsize, out_fmt;
	int rows, cols, linesize, subsample_422;

	/* make sure params don't change while we are decoding */
	mutex_lock(&cam->param_lock);

	obuf = cam->decompressed_frame.data;
	end_obuf = obuf+CPIA_MAX_FRAME_SIZE;
	ibuf = cam->raw_image;
	origsize = size;
	out_fmt = cam->vp.palette;

	if ((ibuf[0] != MAGIC_0) || (ibuf[1] != MAGIC_1)) {
		LOG("header not found\n");
		mutex_unlock(&cam->param_lock);
		return -1;
	}

	if ((ibuf[16] != VIDEOSIZE_QCIF) && (ibuf[16] != VIDEOSIZE_CIF)) {
		LOG("wrong video size\n");
		mutex_unlock(&cam->param_lock);
		return -1;
	}

	if (ibuf[17] != SUBSAMPLE_420 && ibuf[17] != SUBSAMPLE_422) {
		LOG("illegal subtype %d\n",ibuf[17]);
		mutex_unlock(&cam->param_lock);
		return -1;
	}
	subsample_422 = ibuf[17] == SUBSAMPLE_422;

	if (ibuf[18] != YUVORDER_YUYV && ibuf[18] != YUVORDER_UYVY) {
		LOG("illegal yuvorder %d\n",ibuf[18]);
		mutex_unlock(&cam->param_lock);
		return -1;
	}
	in_uyvy = ibuf[18] == YUVORDER_UYVY;

	if ((ibuf[24] != cam->params.roi.colStart) ||
	    (ibuf[25] != cam->params.roi.colEnd) ||
	    (ibuf[26] != cam->params.roi.rowStart) ||
	    (ibuf[27] != cam->params.roi.rowEnd)) {
		LOG("ROI mismatch\n");
		mutex_unlock(&cam->param_lock);
		return -1;
	}
	cols = 8*(ibuf[25] - ibuf[24]);
	rows = 4*(ibuf[27] - ibuf[26]);


	if ((ibuf[28] != NOT_COMPRESSED) && (ibuf[28] != COMPRESSED)) {
		LOG("illegal compression %d\n",ibuf[28]);
		mutex_unlock(&cam->param_lock);
		return -1;
	}
	compressed = (ibuf[28] == COMPRESSED);

	if (ibuf[29] != NO_DECIMATION && ibuf[29] != DECIMATION_ENAB) {
		LOG("illegal decimation %d\n",ibuf[29]);
		mutex_unlock(&cam->param_lock);
		return -1;
	}
	decimation = (ibuf[29] == DECIMATION_ENAB);

	cam->params.yuvThreshold.yThreshold = ibuf[30];
	cam->params.yuvThreshold.uvThreshold = ibuf[31];
	cam->params.status.systemState = ibuf[32];
	cam->params.status.grabState = ibuf[33];
	cam->params.status.streamState = ibuf[34];
	cam->params.status.fatalError = ibuf[35];
	cam->params.status.cmdError = ibuf[36];
	cam->params.status.debugFlags = ibuf[37];
	cam->params.status.vpStatus = ibuf[38];
	cam->params.status.errorCode = ibuf[39];
	cam->fps = ibuf[41];
	mutex_unlock(&cam->param_lock);

	linesize = skipcount(cols, out_fmt);
	ibuf += FRAME_HEADER_SIZE;
	size -= FRAME_HEADER_SIZE;
	ll = ibuf[0] | (ibuf[1] << 8);
	ibuf += 2;
	even_line = 1;

	while (size > 0) {
		size -= (ll+2);
		if (size < 0) {
			LOG("Insufficient data in buffer\n");
			return -1;
		}

		while (ll > 1) {
			if (!compressed || (compressed && !(*ibuf & 1))) {
				if(subsample_422 || even_line) {
				obuf += yuvconvert(ibuf, obuf, out_fmt,
						   in_uyvy, cam->mmap_kludge);
				ibuf += 4;
				ll -= 4;
			} else {
					/* SUBSAMPLE_420 on an odd line */
					obuf += convert420(ibuf, obuf,
							   out_fmt, linesize,
							   cam->mmap_kludge);
					ibuf += 2;
					ll -= 2;
				}
			} else {
				/*skip compressed interval from previous frame*/
				obuf += skipcount(*ibuf >> 1, out_fmt);
				if (obuf > end_obuf) {
					LOG("Insufficient buffer size\n");
					return -1;
				}
				++ibuf;
				ll--;
			}
		}
		if (ll == 1) {
			if (*ibuf != EOL) {
				DBG("EOL not found giving up after %d/%d"
				    " bytes\n", origsize-size, origsize);
				return -1;
			}

			++ibuf; /* skip over EOL */

			if ((size > 3) && (ibuf[0] == EOI) && (ibuf[1] == EOI) &&
			   (ibuf[2] == EOI) && (ibuf[3] == EOI)) {
				size -= 4;
				break;
			}

			if(decimation) {
				/* skip the odd lines for now */
				obuf += linesize;
			}

			if (size > 1) {
				ll = ibuf[0] | (ibuf[1] << 8);
				ibuf += 2; /* skip over line length */
			}
			if(!decimation)
				even_line = !even_line;
		} else {
			LOG("line length was not 1 but %d after %d/%d bytes\n",
			    ll, origsize-size, origsize);
			return -1;
		}
	}

	if(decimation) {
		/* interpolate odd rows */
		int i, j;
		u8 *prev, *next;
		prev = cam->decompressed_frame.data;
		obuf = prev+linesize;
		next = obuf+linesize;
		for(i=1; i<rows-1; i+=2) {
			for(j=0; j<linesize; ++j) {
				*obuf++ = ((int)*prev++ + *next++) / 2;
			}
			prev += linesize;
			obuf += linesize;
			next += linesize;
		}
		/* last row is odd, just copy previous row */
		memcpy(obuf, prev, linesize);
	}

	cam->decompressed_frame.count = obuf-cam->decompressed_frame.data;

	return cam->decompressed_frame.count;
}