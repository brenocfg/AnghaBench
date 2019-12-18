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
struct omapfb_plane_info {scalar_t__ yoffset; scalar_t__ size; scalar_t__ enabled; } ;
struct omapfb_mem_info {scalar_t__ yoffset; scalar_t__ size; scalar_t__ enabled; } ;
struct fb_var_screeninfo {scalar_t__ yoffset; scalar_t__ size; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 int /*<<< orphan*/  FBIOPAN_DISPLAY ; 
 int /*<<< orphan*/  KDSETMODE ; 
 struct omapfb_plane_info* KD_TEXT ; 
 int /*<<< orphan*/  OMAPFB_QUERY_MEM ; 
 int /*<<< orphan*/  OMAPFB_QUERY_PLANE ; 
 int /*<<< orphan*/  OMAPFB_SETUP_MEM ; 
 int /*<<< orphan*/  OMAPFB_SETUP_PLANE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct omapfb_plane_info*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
	struct fb_var_screeninfo fbvar;
	struct omapfb_plane_info pi;
	struct omapfb_mem_info mi;
	int ret, fbdev, kbdfd;

	fbdev = open("/dev/fb0", O_RDWR);
	if (fbdev == -1) {
		perror("open fb0");
		goto end_fb0;
	}

	ret = ioctl(fbdev, FBIOGET_VSCREENINFO, &fbvar);
	if (ret == -1) {
		perror("FBIOGET_VSCREENINFO ioctl");
		goto end_fb0;
	}

	if (fbvar.yoffset != 0) {
		printf("fixing yoffset.. ");
		fbvar.yoffset = 0;
		ret = ioctl(fbdev, FBIOPAN_DISPLAY, &fbvar);
		if (ret < 0)
			perror("ioctl FBIOPAN_DISPLAY");
		else
			printf("ok\n");
	}

end_fb0:
	if (fbdev >= 0)
		close(fbdev);

	fbdev = open("/dev/fb1", O_RDWR);
	if (fbdev == -1) {
		perror("open fb1");
		goto end_fb1;
	}

	ret  = ioctl(fbdev, OMAPFB_QUERY_PLANE, &pi);
	ret |= ioctl(fbdev, OMAPFB_QUERY_MEM, &mi);
	if (ret != 0)
		perror("QUERY_*");

	pi.enabled = 0;
	ret = ioctl(fbdev, OMAPFB_SETUP_PLANE, &pi);
	if (ret != 0)
		perror("SETUP_PLANE");

	mi.size = 0;
	ret = ioctl(fbdev, OMAPFB_SETUP_MEM, &mi);
	if (ret != 0)
		perror("SETUP_MEM");

end_fb1:
	if (fbdev >= 0)
		close(fbdev);

	kbdfd = open("/dev/tty", O_RDWR);
	if (kbdfd == -1) {
		perror("open /dev/tty");
		return 1;
	}

	if (ioctl(kbdfd, KDSETMODE, KD_TEXT) == -1)
		perror("KDSETMODE KD_TEXT");

	close(kbdfd);

	return 0;
}