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
struct TYPE_4__ {int n_buffers; struct buffer* buffers; int /*<<< orphan*/  fd; int /*<<< orphan*/  dev_name; } ;
typedef  TYPE_2__ video4linux_t ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct v4l2_requestbuffers {int count; int index; TYPE_1__ m; int /*<<< orphan*/  length; void* memory; void* type; int /*<<< orphan*/  member_0; } ;
struct v4l2_buffer {int count; int index; TYPE_1__ m; int /*<<< orphan*/  length; void* memory; void* type; int /*<<< orphan*/  member_0; } ;
struct buffer {int /*<<< orphan*/  start; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 void* V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDIOC_QUERYBUF ; 
 int /*<<< orphan*/  VIDIOC_REQBUFS ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static bool init_mmap(void *data)
{
   struct v4l2_requestbuffers req = {0};
   video4linux_t *v4l             = (video4linux_t*)data;

   req.count                      = 4;
   req.type                       = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   req.memory                     = V4L2_MEMORY_MMAP;

   if (xioctl(v4l->fd, VIDIOC_REQBUFS, &req) == -1)
   {
      if (errno == EINVAL)
         RARCH_ERR("[V4L2]: %s does not support memory mapping.\n", v4l->dev_name);
      else
         RARCH_ERR("[V4L2]: xioctl of VIDIOC_REQBUFS failed.\n");
      return false;
   }

   if (req.count < 2)
   {
      RARCH_ERR("[V4L2]: Insufficient buffer memory on %s.\n", v4l->dev_name);
      return false;
   }

   v4l->buffers = (struct buffer*)calloc(req.count, sizeof(*v4l->buffers));

   if (!v4l->buffers)
   {
      RARCH_ERR("[V4L2]: Out of memory allocating V4L2 buffers.\n");
      return false;
   }

   for (v4l->n_buffers = 0; v4l->n_buffers < req.count; v4l->n_buffers++)
   {
      struct v4l2_buffer buf = {0};

      buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index  = v4l->n_buffers;

      if (xioctl(v4l->fd, VIDIOC_QUERYBUF, &buf) == -1)
      {
         RARCH_ERR("[V4L2]: Error - xioctl VIDIOC_QUERYBUF.\n");
         return false;
      }

      v4l->buffers[v4l->n_buffers].length = buf.length;
      v4l->buffers[v4l->n_buffers].start  = mmap(NULL,
            buf.length, PROT_READ | PROT_WRITE,
            MAP_SHARED,
            v4l->fd, buf.m.offset);

      if (v4l->buffers[v4l->n_buffers].start == MAP_FAILED)
      {
         RARCH_ERR("[V4L2]: Error - mmap.\n");
         return false;
      }
   }

   return true;
}