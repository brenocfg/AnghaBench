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
typedef  int /*<<< orphan*/  uint32_t ;
struct modeset_buf {int /*<<< orphan*/  map; scalar_t__ size; scalar_t__ handle; scalar_t__ stride; int /*<<< orphan*/  fb_id; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_mode_map_dumb {int bpp; int depth; int /*<<< orphan*/  offset; scalar_t__ handle; scalar_t__ size; scalar_t__ pitch; int /*<<< orphan*/  fb_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
struct drm_mode_fb_cmd {int bpp; int depth; int /*<<< orphan*/  offset; scalar_t__ handle; scalar_t__ size; scalar_t__ pitch; int /*<<< orphan*/  fb_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
struct drm_mode_create_dumb {int bpp; int depth; int /*<<< orphan*/  offset; scalar_t__ handle; scalar_t__ size; scalar_t__ pitch; int /*<<< orphan*/  fb_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_MODE_ADDFB ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_CREATE_DUMB ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_MAP_DUMB ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 TYPE_1__ drm ; 
 int /*<<< orphan*/  drmIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_mode_map_dumb*) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int modeset_create_dumbfb(int fd, struct modeset_buf *buf,
      int bpp, uint32_t pixformat)
{
   struct drm_mode_create_dumb create_dumb = {0};
   struct drm_mode_map_dumb map_dumb       = {0};
   struct drm_mode_fb_cmd cmd_dumb         = {0};

   create_dumb.width  = buf->width;
   create_dumb.height = buf->height;
   create_dumb.bpp    = bpp * 8;
   create_dumb.flags  = 0;
   create_dumb.pitch  = 0;
   create_dumb.size   = 0;
   create_dumb.handle = 0;
   drmIoctl(drm.fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_dumb);

   /* Create the buffer. We just copy values here... */
   cmd_dumb.width        = create_dumb.width;
   cmd_dumb.height       = create_dumb.height;
   cmd_dumb.bpp          = create_dumb.bpp;
   cmd_dumb.pitch        = create_dumb.pitch;
   cmd_dumb.handle       = create_dumb.handle;
   cmd_dumb.depth        = 24;

   /* Map the buffer */
   drmIoctl(drm.fd,DRM_IOCTL_MODE_ADDFB,&cmd_dumb);
   map_dumb.handle=create_dumb.handle;
   drmIoctl(drm.fd,DRM_IOCTL_MODE_MAP_DUMB,&map_dumb);

   buf->pixel_format = pixformat;
   buf->fb_id = cmd_dumb.fb_id;
   buf->stride = create_dumb.pitch;
   buf->size = create_dumb.size;
   buf->handle = create_dumb.handle;

   /* Get address */
   buf->map = mmap(0, buf->size, PROT_READ | PROT_WRITE, MAP_SHARED,
         fd, map_dumb.offset);
   if (buf->map == MAP_FAILED)
   {
      RARCH_ERR ("DRM: cannot mmap dumb buffer\n");
      return 0;
   }

   return 0;
}