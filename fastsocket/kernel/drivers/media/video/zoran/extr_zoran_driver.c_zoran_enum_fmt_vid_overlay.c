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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int dummy; } ;
struct v4l2_fmtdesc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZORAN_FORMAT_OVERLAY ; 
 int zoran_enum_fmt (struct zoran*,struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zoran_enum_fmt_vid_overlay(struct file *file, void *__fh,
					    struct v4l2_fmtdesc *f)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	return zoran_enum_fmt(zr, f, ZORAN_FORMAT_OVERLAY);
}