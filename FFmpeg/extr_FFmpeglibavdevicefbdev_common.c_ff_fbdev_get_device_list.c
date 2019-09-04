#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {char* id; } ;
struct fb_fix_screeninfo {char* id; } ;
typedef  int /*<<< orphan*/  device_file ;
struct TYPE_9__ {struct TYPE_9__* device_description; struct TYPE_9__* device_name; } ;
struct TYPE_8__ {scalar_t__ nb_devices; scalar_t__ default_device; int /*<<< orphan*/  devices; } ;
typedef  TYPE_1__ AVDeviceInfoList ;
typedef  TYPE_2__ AVDeviceInfo ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FBIOGET_FSCREENINFO ; 
 int /*<<< orphan*/  FBIOGET_VSCREENINFO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int av_dynarray_add_nofree (int /*<<< orphan*/ *,scalar_t__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_mallocz (int) ; 
 void* av_strdup (char*) ; 
 int avpriv_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 char* ff_fbdev_default_device () ; 
 int ioctl (int,int /*<<< orphan*/ ,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (TYPE_2__*,char const*) ; 

int ff_fbdev_get_device_list(AVDeviceInfoList *device_list)
{
    struct fb_var_screeninfo varinfo;
    struct fb_fix_screeninfo fixinfo;
    char device_file[12];
    AVDeviceInfo *device = NULL;
    int i, fd, ret = 0;
    const char *default_device = ff_fbdev_default_device();

    if (!device_list)
        return AVERROR(EINVAL);

    for (i = 0; i <= 31; i++) {
        snprintf(device_file, sizeof(device_file), "/dev/fb%d", i);

        if ((fd = avpriv_open(device_file, O_RDWR)) < 0) {
            int err = AVERROR(errno);
            if (err != AVERROR(ENOENT))
                av_log(NULL, AV_LOG_ERROR, "Could not open framebuffer device '%s': %s\n",
                       device_file, av_err2str(err));
            continue;
        }
        if (ioctl(fd, FBIOGET_VSCREENINFO, &varinfo) == -1)
            goto fail_device;
        if (ioctl(fd, FBIOGET_FSCREENINFO, &fixinfo) == -1)
            goto fail_device;

        device = av_mallocz(sizeof(AVDeviceInfo));
        if (!device) {
            ret = AVERROR(ENOMEM);
            goto fail_device;
        }
        device->device_name = av_strdup(device_file);
        device->device_description = av_strdup(fixinfo.id);
        if (!device->device_name || !device->device_description) {
            ret = AVERROR(ENOMEM);
            goto fail_device;
        }

        if ((ret = av_dynarray_add_nofree(&device_list->devices,
                                          &device_list->nb_devices, device)) < 0)
            goto fail_device;

        if (default_device && !strcmp(device->device_name, default_device)) {
            device_list->default_device = device_list->nb_devices - 1;
            default_device = NULL;
        }
        close(fd);
        continue;

      fail_device:
        if (device) {
            av_freep(&device->device_name);
            av_freep(&device->device_description);
            av_freep(&device);
        }
        if (fd >= 0)
            close(fd);
        if (ret < 0)
            return ret;
    }
    return 0;
}