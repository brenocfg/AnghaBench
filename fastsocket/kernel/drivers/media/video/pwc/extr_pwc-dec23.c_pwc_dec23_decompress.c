#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int y; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {int y; int x; } ;
struct pwc_device {TYPE_3__ view; int /*<<< orphan*/  vbandlength; TYPE_2__ image; int /*<<< orphan*/  decompress_data; TYPE_1__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DecompressBand23 (int /*<<< orphan*/ ,void const*,unsigned char*,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DecompressBandBayer (int /*<<< orphan*/ ,void const*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int PWCX_FLAG_BAYER ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void pwc_dec23_decompress(const struct pwc_device *pwc,
			  const void *src,
			  void *dst,
			  int flags)
{
	int bandlines_left, stride, bytes_per_block;

	bandlines_left = pwc->image.y / 4;
	bytes_per_block = pwc->view.x * 4;

	if (flags & PWCX_FLAG_BAYER) {
#if ENABLE_BAYER_DECODER
		/* RGB Bayer format */
		unsigned char *rgbout;

		stride = pwc->view.x * pwc->offset.y;
		rgbout = dst + stride + pwc->offset.x;


		while (bandlines_left--) {

			DecompressBandBayer(pwc->decompress_data,
					    src,
					    rgbout,
					    pwc->image.x, pwc->view.x);

			src += pwc->vbandlength;
			rgbout += bytes_per_block;

		}
#else
		memset(dst, 0, pwc->view.x * pwc->view.y);
#endif

	} else {
		/* YUV420P image format */
		unsigned char *pout_planar_y;
		unsigned char *pout_planar_u;
		unsigned char *pout_planar_v;
		unsigned int   plane_size;

		plane_size = pwc->view.x * pwc->view.y;

		/* offset in Y plane */
		stride = pwc->view.x * pwc->offset.y;
		pout_planar_y = dst + stride + pwc->offset.x;

		/* offsets in U/V planes */
		stride = (pwc->view.x * pwc->offset.y) / 4 + pwc->offset.x / 2;
		pout_planar_u = dst + plane_size + stride;
		pout_planar_v = dst + plane_size + plane_size / 4 + stride;

		while (bandlines_left--) {

			DecompressBand23(pwc->decompress_data,
					 src,
					 pout_planar_y, pout_planar_u, pout_planar_v,
					 pwc->image.x, pwc->view.x);
			src += pwc->vbandlength;
			pout_planar_y += bytes_per_block;
			pout_planar_u += pwc->view.x;
			pout_planar_v += pwc->view.x;

		}

	}

}