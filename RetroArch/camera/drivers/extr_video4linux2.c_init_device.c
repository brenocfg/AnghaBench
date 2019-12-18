#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  pitch; int /*<<< orphan*/  fd; int /*<<< orphan*/  dev_name; } ;
typedef  TYPE_3__ video4linux_t ;
struct TYPE_5__ {int width; scalar_t__ pixelformat; scalar_t__ field; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; } ;
struct TYPE_6__ {TYPE_1__ pix; } ;
struct v4l2_format {int capabilities; TYPE_2__ fmt; void* type; int /*<<< orphan*/  defrect; int /*<<< orphan*/  c; int /*<<< orphan*/  member_0; } ;
struct v4l2_cropcap {int capabilities; TYPE_2__ fmt; void* type; int /*<<< orphan*/  defrect; int /*<<< orphan*/  c; int /*<<< orphan*/  member_0; } ;
struct v4l2_crop {int capabilities; TYPE_2__ fmt; void* type; int /*<<< orphan*/  defrect; int /*<<< orphan*/  c; int /*<<< orphan*/  member_0; } ;
struct v4l2_capability {int capabilities; TYPE_2__ fmt; void* type; int /*<<< orphan*/  defrect; int /*<<< orphan*/  c; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,int /*<<< orphan*/ ) ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  VIDIOC_CROPCAP ; 
 int /*<<< orphan*/  VIDIOC_QUERYCAP ; 
 int /*<<< orphan*/  VIDIOC_S_CROP ; 
 int /*<<< orphan*/  VIDIOC_S_FMT ; 
 scalar_t__ errno ; 
 int init_mmap (TYPE_3__*) ; 
 scalar_t__ xioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 

__attribute__((used)) static bool init_device(void *data)
{
   struct v4l2_crop crop;
   struct v4l2_capability cap;
   struct v4l2_format      fmt = {0};
   struct v4l2_cropcap cropcap = {0};
   video4linux_t          *v4l = (video4linux_t*)data;

   if (xioctl(v4l->fd, VIDIOC_QUERYCAP, &cap) < 0)
   {
      if (errno == EINVAL)
         RARCH_ERR("[V4L2]: %s is no V4L2 device.\n", v4l->dev_name);
      else
         RARCH_ERR("[V4L2]: Error - VIDIOC_QUERYCAP.\n");
      return false;
   }

   if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
   {
      RARCH_ERR("[V4L2]: %s is no video capture device.\n", v4l->dev_name);
      return false;
   }

   if (!(cap.capabilities & V4L2_CAP_STREAMING))
   {
      RARCH_ERR("[V4L2]: %s does not support streaming I/O (V4L2_CAP_STREAMING).\n",
            v4l->dev_name);
      return false;
   }

   cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

   if (xioctl(v4l->fd, VIDIOC_CROPCAP, &cropcap) == 0)
   {
      crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      crop.c    = cropcap.defrect;
      /* Ignore errors here. */
      xioctl(v4l->fd, VIDIOC_S_CROP, &crop);
   }

   fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   fmt.fmt.pix.width       = v4l->width;
   fmt.fmt.pix.height      = v4l->height;
   fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
   fmt.fmt.pix.field       = V4L2_FIELD_NONE;

   if (xioctl(v4l->fd, VIDIOC_S_FMT, &fmt) < 0)
   {
      RARCH_ERR("[V4L2]: Error - VIDIOC_S_FMT\n");
      return false;
   }

   /* VIDIOC_S_FMT may change width, height and pitch. */
   v4l->width  = fmt.fmt.pix.width;
   v4l->height = fmt.fmt.pix.height;
   v4l->pitch  = MAX(fmt.fmt.pix.bytesperline, v4l->width * 2);

   /* Sanity check to see if our assumptions are met.
    * It is possible to support whatever the device gives us,
    * but this dramatically increases complexity.
    */
   if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV)
   {
      RARCH_ERR("[V4L2]: The V4L2 device doesn't support YUYV.\n");
      return false;
   }

   if (fmt.fmt.pix.field != V4L2_FIELD_NONE
         && fmt.fmt.pix.field != V4L2_FIELD_INTERLACED)
   {
      RARCH_ERR("[V4L2]: The V4L2 device doesn't support progressive nor interlaced video.\n");
      return false;
   }

   RARCH_LOG("[V4L2]: device: %u x %u.\n", v4l->width, v4l->height);

   return init_mmap(v4l);
}