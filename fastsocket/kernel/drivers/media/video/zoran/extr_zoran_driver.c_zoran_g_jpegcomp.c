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
struct TYPE_3__ {int /*<<< orphan*/  jpeg_markers; int /*<<< orphan*/  COM_len; int /*<<< orphan*/  COM_data; int /*<<< orphan*/  APP_len; int /*<<< orphan*/  APP_data; int /*<<< orphan*/  APPn; int /*<<< orphan*/  quality; } ;
struct TYPE_4__ {TYPE_1__ jpg_comp; } ;
struct zoran_fh {TYPE_2__ jpg_settings; struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  resource_lock; } ;
struct v4l2_jpegcompression {int /*<<< orphan*/  jpeg_markers; int /*<<< orphan*/  COM_len; int /*<<< orphan*/  COM_data; int /*<<< orphan*/  APP_len; int /*<<< orphan*/  APP_data; int /*<<< orphan*/  APPn; int /*<<< orphan*/  quality; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_jpegcompression*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zoran_g_jpegcomp(struct file *file, void *__fh,
					struct v4l2_jpegcompression *params)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;
	memset(params, 0, sizeof(*params));

	mutex_lock(&zr->resource_lock);

	params->quality = fh->jpg_settings.jpg_comp.quality;
	params->APPn = fh->jpg_settings.jpg_comp.APPn;
	memcpy(params->APP_data,
	       fh->jpg_settings.jpg_comp.APP_data,
	       fh->jpg_settings.jpg_comp.APP_len);
	params->APP_len = fh->jpg_settings.jpg_comp.APP_len;
	memcpy(params->COM_data,
	       fh->jpg_settings.jpg_comp.COM_data,
	       fh->jpg_settings.jpg_comp.COM_len);
	params->COM_len = fh->jpg_settings.jpg_comp.COM_len;
	params->jpeg_markers =
	    fh->jpg_settings.jpg_comp.jpeg_markers;

	mutex_unlock(&zr->resource_lock);

	return 0;
}