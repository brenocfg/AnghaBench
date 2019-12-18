#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_jpegcompression {int APP_len; int COM_len; int jpeg_markers; int APPn; int /*<<< orphan*/  COM_data; int /*<<< orphan*/  APP_data; } ;
struct TYPE_3__ {int inhibit_htables; } ;
struct TYPE_4__ {TYPE_1__ compression; } ;
struct camera_data {int APPn; int APP_len; int COM_len; int /*<<< orphan*/  COM_data; int /*<<< orphan*/  APP_data; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOG (char*,int,...) ; 
 int V4L2_JPEG_MARKER_DHT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ioctl_s_jpegcomp(void *arg,struct camera_data *cam)
{
	struct v4l2_jpegcompression *parms = arg;

	DBG("S_JPEGCOMP APP_len:%d COM_len:%d\n",
	    parms->APP_len, parms->COM_len);

	cam->params.compression.inhibit_htables =
		!(parms->jpeg_markers & V4L2_JPEG_MARKER_DHT);

	if(parms->APP_len != 0) {
		if(parms->APP_len > 0 &&
		   parms->APP_len <= sizeof(cam->APP_data) &&
		   parms->APPn >= 0 && parms->APPn <= 15) {
			cam->APPn = parms->APPn;
			cam->APP_len = parms->APP_len;
			memcpy(cam->APP_data, parms->APP_data, parms->APP_len);
		} else {
			LOG("Bad APPn Params n=%d len=%d\n",
			    parms->APPn, parms->APP_len);
			return -EINVAL;
		}
	} else {
		cam->APP_len = 0;
	}

	if(parms->COM_len != 0) {
		if(parms->COM_len > 0 &&
		   parms->COM_len <= sizeof(cam->COM_data)) {
			cam->COM_len = parms->COM_len;
			memcpy(cam->COM_data, parms->COM_data, parms->COM_len);
		} else {
			LOG("Bad COM_len=%d\n", parms->COM_len);
			return -EINVAL;
		}
	}

	return 0;
}