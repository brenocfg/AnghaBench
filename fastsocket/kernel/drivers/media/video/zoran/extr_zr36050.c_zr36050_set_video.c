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
struct zr36050 {int width; int height; int total_code_vol; int real_code_vol; int /*<<< orphan*/  max_block_vol; int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;
struct vfe_settings {int width; int height; int decimation; int quality; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct vfe_polarity {int dummy; } ;
struct tvnorm {int /*<<< orphan*/  VStart; int /*<<< orphan*/  HStart; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR050_MBCV ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  zr36050_write (struct zr36050*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zr36050_set_video (struct videocodec   *codec,
		   struct tvnorm       *norm,
		   struct vfe_settings *cap,
		   struct vfe_polarity *pol)
{
	struct zr36050 *ptr = (struct zr36050 *) codec->data;
	int size;

	dprintk(2, "%s: set_video %d.%d, %d/%d-%dx%d (0x%x) q%d call\n",
		ptr->name, norm->HStart, norm->VStart,
		cap->x, cap->y, cap->width, cap->height,
		cap->decimation, cap->quality);
	/* if () return -EINVAL;
	 * trust the master driver that it knows what it does - so
	 * we allow invalid startx/y and norm for now ... */
	ptr->width = cap->width / (cap->decimation & 0xff);
	ptr->height = cap->height / ((cap->decimation >> 8) & 0xff);

	/* (KM) JPEG quality */
	size = ptr->width * ptr->height;
	size *= 16; /* size in bits */
	/* apply quality setting */
	size = size * cap->quality / 200;

	/* Minimum: 1kb */
	if (size < 8192)
		size = 8192;
	/* Maximum: 7/8 of code buffer */
	if (size > ptr->total_code_vol * 7)
		size = ptr->total_code_vol * 7;

	ptr->real_code_vol = size >> 3; /* in bytes */

	/* Set max_block_vol here (previously in zr36050_init, moved
	 * here for consistency with zr36060 code */
	zr36050_write(ptr, ZR050_MBCV, ptr->max_block_vol);

	return 0;
}