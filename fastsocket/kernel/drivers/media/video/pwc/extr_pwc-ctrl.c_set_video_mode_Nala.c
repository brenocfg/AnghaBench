#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int x; int y; } ;
struct pwc_device {scalar_t__ pixfmt; int release; int cmd_len; unsigned char* cmd_buf; int vframes; int vsize; scalar_t__ valternate; int frame_size; int vbandlength; TYPE_1__ image; int /*<<< orphan*/  decompress_data; int /*<<< orphan*/  type; int /*<<< orphan*/  vendpoint; } ;
struct Nala_table_entry {scalar_t__ alternate; unsigned char* mode; scalar_t__ compressed; } ;

/* Variables and functions */
 int EINVAL ; 
 struct Nala_table_entry** Nala_table ; 
 int PSZ_CIF ; 
 int /*<<< orphan*/  PWC_DEBUG_MODULE (char*,int) ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  pwc_dec1_init (int /*<<< orphan*/ ,int,unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pwc_image_sizes ; 
 int send_video_command (struct pwc_device*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int set_video_mode_Nala(struct pwc_device *pdev, int size, int frames)
{
	unsigned char buf[3];
	int ret, fps;
	struct Nala_table_entry *pEntry;
	int frames2frames[31] =
	{ /* closest match of framerate */
	   0,  0,  0,  0,  4,  /*  0-4  */
	   5,  5,  7,  7, 10,  /*  5-9  */
	  10, 10, 12, 12, 15,  /* 10-14 */
	  15, 15, 15, 20, 20,  /* 15-19 */
	  20, 20, 20, 24, 24,  /* 20-24 */
	  24, 24, 24, 24, 24,  /* 25-29 */
	  24                   /* 30    */
	};
	int frames2table[31] =
	{ 0, 0, 0, 0, 0, /*  0-4  */
	  1, 1, 1, 2, 2, /*  5-9  */
	  3, 3, 4, 4, 4, /* 10-14 */
	  5, 5, 5, 5, 5, /* 15-19 */
	  6, 6, 6, 6, 7, /* 20-24 */
	  7, 7, 7, 7, 7, /* 25-29 */
	  7              /* 30    */
	};

	if (size < 0 || size > PSZ_CIF || frames < 4 || frames > 25)
		return -EINVAL;
	frames = frames2frames[frames];
	fps = frames2table[frames];
	pEntry = &Nala_table[size][fps];
	if (pEntry->alternate == 0)
		return -EINVAL;

	memcpy(buf, pEntry->mode, 3);
	ret = send_video_command(pdev, pdev->vendpoint, buf, 3);
	if (ret < 0) {
		PWC_DEBUG_MODULE("Failed to send video command... %d\n", ret);
		return ret;
	}
	if (pEntry->compressed && pdev->pixfmt == V4L2_PIX_FMT_YUV420)
		pwc_dec1_init(pdev->type, pdev->release, buf, pdev->decompress_data);

	pdev->cmd_len = 3;
	memcpy(pdev->cmd_buf, buf, 3);

	/* Set various parameters */
	pdev->vframes = frames;
	pdev->vsize = size;
	pdev->valternate = pEntry->alternate;
	pdev->image = pwc_image_sizes[size];
	pdev->frame_size = (pdev->image.x * pdev->image.y * 3) / 2;
	if (pEntry->compressed) {
		if (pdev->release < 5) { /* 4 fold compression */
			pdev->vbandlength = 528;
			pdev->frame_size /= 4;
		}
		else {
			pdev->vbandlength = 704;
			pdev->frame_size /= 3;
		}
	}
	else
		pdev->vbandlength = 0;
	return 0;
}