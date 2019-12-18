#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  videosize_t ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOSIZE_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOSIZE_Y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbvideo_VideosizeToString(char *buf, int bufLen, videosize_t vs)
{
	char tmp[40];
	int n;

	n = 1 + sprintf(tmp, "%ldx%ld", VIDEOSIZE_X(vs), VIDEOSIZE_Y(vs));
	assert(n < sizeof(tmp));
	if ((buf == NULL) || (bufLen < n))
		err("usbvideo_VideosizeToString: buffer is too small.");
	else
		memmove(buf, tmp, n);
}