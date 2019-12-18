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
struct v4l2_pix_format {int height; int bytesperline; int pixelformat; } ;
struct cafe_camera {struct v4l2_pix_format pix_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  C0_DF_MASK ; 
 int C0_DF_RGB ; 
 int C0_DF_YUV ; 
 int C0_RGB4_XRGB ; 
 int C0_RGB5_BGGR ; 
 int C0_RGBF_444 ; 
 int C0_RGBF_565 ; 
 int /*<<< orphan*/  C0_SIFM_MASK ; 
 int C0_SIF_HVSYNC ; 
 int C0_YUVE_YUYV ; 
 int C0_YUV_PACKED ; 
 int /*<<< orphan*/  IMGP_YP_MASK ; 
 int IMGSZ_H_MASK ; 
 int IMGSZ_V_MASK ; 
 int IMGSZ_V_SHIFT ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  REG_IMGOFFSET ; 
 int /*<<< orphan*/  REG_IMGPITCH ; 
 int /*<<< orphan*/  REG_IMGSIZE ; 
#define  V4L2_PIX_FMT_RGB444 130 
#define  V4L2_PIX_FMT_RGB565 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  cafe_reg_write (struct cafe_camera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cafe_reg_write_mask (struct cafe_camera*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*,int) ; 

__attribute__((used)) static void cafe_ctlr_image(struct cafe_camera *cam)
{
	int imgsz;
	struct v4l2_pix_format *fmt = &cam->pix_format;

	imgsz = ((fmt->height << IMGSZ_V_SHIFT) & IMGSZ_V_MASK) |
		(fmt->bytesperline & IMGSZ_H_MASK);
	cafe_reg_write(cam, REG_IMGSIZE, imgsz);
	cafe_reg_write(cam, REG_IMGOFFSET, 0);
	/* YPITCH just drops the last two bits */
	cafe_reg_write_mask(cam, REG_IMGPITCH, fmt->bytesperline,
			IMGP_YP_MASK);
	/*
	 * Tell the controller about the image format we are using.
	 */
	switch (cam->pix_format.pixelformat) {
	case V4L2_PIX_FMT_YUYV:
	    cafe_reg_write_mask(cam, REG_CTRL0,
			    C0_DF_YUV|C0_YUV_PACKED|C0_YUVE_YUYV,
			    C0_DF_MASK);
	    break;

	case V4L2_PIX_FMT_RGB444:
	    cafe_reg_write_mask(cam, REG_CTRL0,
			    C0_DF_RGB|C0_RGBF_444|C0_RGB4_XRGB,
			    C0_DF_MASK);
		/* Alpha value? */
	    break;

	case V4L2_PIX_FMT_RGB565:
	    cafe_reg_write_mask(cam, REG_CTRL0,
			    C0_DF_RGB|C0_RGBF_565|C0_RGB5_BGGR,
			    C0_DF_MASK);
	    break;

	default:
	    cam_err(cam, "Unknown format %x\n", cam->pix_format.pixelformat);
	    break;
	}
	/*
	 * Make sure it knows we want to use hsync/vsync.
	 */
	cafe_reg_write_mask(cam, REG_CTRL0, C0_SIF_HVSYNC,
			C0_SIFM_MASK);
}