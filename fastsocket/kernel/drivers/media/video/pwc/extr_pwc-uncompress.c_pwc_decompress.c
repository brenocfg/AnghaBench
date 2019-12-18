#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pwc_raw_frame {struct pwc_raw_frame* cmd; void* vbandlength; void* type; } ;
struct pwc_frame_buf {void* data; } ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_7__ {int x; int y; } ;
struct TYPE_6__ {int y; int x; } ;
struct pwc_device {size_t fill_image; int frame_header_size; scalar_t__ pixfmt; scalar_t__ type; scalar_t__ vbandlength; void* cmd_buf; int frame_size; scalar_t__ vsize; int vframes; scalar_t__ vsnapshot; TYPE_4__ image; TYPE_3__ view; TYPE_2__ offset; TYPE_1__* images; void* image_data; struct pwc_frame_buf* read_frame; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (scalar_t__) ; 
 int EFAULT ; 
 int ENXIO ; 
 scalar_t__ PSZ_VGA ; 
 int /*<<< orphan*/  PWCX_FLAG_PLANAR ; 
 int /*<<< orphan*/  PWC_ERROR (char*) ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct pwc_raw_frame*,void*,int) ; 
 int /*<<< orphan*/  pwc_dec23_decompress (struct pwc_device*,void*,void*,int /*<<< orphan*/ ) ; 

int pwc_decompress(struct pwc_device *pdev)
{
	struct pwc_frame_buf *fbuf;
	int n, line, col, stride;
	void *yuv, *image;
	u16 *src;
	u16 *dsty, *dstu, *dstv;

	if (pdev == NULL)
		return -EFAULT;

	fbuf = pdev->read_frame;
	if (fbuf == NULL)
		return -EFAULT;
	image  = pdev->image_data;
	image += pdev->images[pdev->fill_image].offset;

	yuv = fbuf->data + pdev->frame_header_size;  /* Skip header */

	/* Raw format; that's easy... */
	if (pdev->pixfmt != V4L2_PIX_FMT_YUV420)
	{
		struct pwc_raw_frame *raw_frame = image;
		raw_frame->type = cpu_to_le16(pdev->type);
		raw_frame->vbandlength = cpu_to_le16(pdev->vbandlength);
			/* cmd_buf is always 4 bytes, but sometimes, only the
			 * first 3 bytes is filled (Nala case). We can
			 * determine this using the type of the webcam */
		memcpy(raw_frame->cmd, pdev->cmd_buf, 4);
		memcpy(raw_frame+1, yuv, pdev->frame_size);
		return 0;
	}

	if (pdev->vbandlength == 0) {
		/* Uncompressed mode.
		 * We copy the data into the output buffer, using the viewport
		 * size (which may be larger than the image size).
		 * Unfortunately we have to do a bit of byte stuffing to get
		 * the desired output format/size.
		 *
		 * We do some byte shuffling here to go from the
		 * native format to YUV420P.
		 */
		src = (u16 *)yuv;
		n = pdev->view.x * pdev->view.y;

		/* offset in Y plane */
		stride = pdev->view.x * pdev->offset.y + pdev->offset.x;
		dsty = (u16 *)(image + stride);

		/* offsets in U/V planes */
		stride = pdev->view.x * pdev->offset.y / 4 + pdev->offset.x / 2;
		dstu = (u16 *)(image + n +         stride);
		dstv = (u16 *)(image + n + n / 4 + stride);

		/* increment after each line */
		stride = (pdev->view.x - pdev->image.x) / 2; /* u16 is 2 bytes */

		for (line = 0; line < pdev->image.y; line++) {
			for (col = 0; col < pdev->image.x; col += 4) {
				*dsty++ = *src++;
				*dsty++ = *src++;
				if (line & 1)
					*dstv++ = *src++;
				else
					*dstu++ = *src++;
			}
			dsty += stride;
			if (line & 1)
				dstv += (stride >> 1);
			else
				dstu += (stride >> 1);
		}

		return 0;
	}

	/*
	 * Compressed;
	 * the decompressor routines will write the data in planar format
	 * immediately.
	 */
	if (pdev->vsize == PSZ_VGA && pdev->vframes == 5 && pdev->vsnapshot) {
		PWC_ERROR("Mode Bayer is not supported for now\n");
		/* flags |= PWCX_FLAG_BAYER; */
		return -ENXIO; /* No such device or address: missing decompressor */
	}

	if (DEVICE_USE_CODEC1(pdev->type)) {

		/* TODO & FIXME */
		PWC_ERROR("This chipset is not supported for now\n");
		return -ENXIO; /* No such device or address: missing decompressor */

	} else {
		pwc_dec23_decompress(pdev, yuv, image, PWCX_FLAG_PLANAR);
	}
	return 0;
}