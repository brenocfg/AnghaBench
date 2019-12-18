#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int num_devices; int /*<<< orphan*/  fd; TYPE_4__** devices; } ;
typedef  TYPE_3__ udev_input_t ;
struct TYPE_8__ {int x_min; int x_max; int y_min; int y_max; } ;
struct TYPE_11__ {int fd; int type; TYPE_1__ mouse; int /*<<< orphan*/  devnode; int /*<<< orphan*/  handle_cb; scalar_t__ dev; } ;
typedef  TYPE_4__ udev_input_device_t ;
struct stat {scalar_t__ st_dev; } ;
struct TYPE_9__ {TYPE_4__* ptr; } ;
struct kevent {TYPE_2__ data; int /*<<< orphan*/  events; } ;
struct input_absinfo {int minimum; int maximum; } ;
struct epoll_event {int dummy; } ;
typedef  enum udev_input_dev_type { ____Placeholder_udev_input_dev_type } udev_input_dev_type ;
typedef  int /*<<< orphan*/  device_handle_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVIOCGABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTENSOCKET ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int,int /*<<< orphan*/ ) ; 
 int UDEV_INPUT_MOUSE ; 
 int UDEV_INPUT_TOUCHPAD ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct kevent*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct input_absinfo*) ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (char const*,int) ; 
 scalar_t__ realloc (TYPE_4__**,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static bool udev_input_add_device(udev_input_t *udev,
      enum udev_input_dev_type type, const char *devnode, device_handle_cb cb)
{
   int fd;
   struct stat st;
#if defined(HAVE_EPOLL)
   struct epoll_event event;
#elif defined(HAVE_KQUEUE)
   struct kevent event;
#endif
   struct input_absinfo absinfo;
   udev_input_device_t **tmp;
   udev_input_device_t *device = NULL;

   st.st_dev                   = 0;

   if (stat(devnode, &st) < 0)
      return false;

   fd = open(devnode, O_RDONLY | O_NONBLOCK);
   if (fd < 0)
      return false;

   device = (udev_input_device_t*)calloc(1, sizeof(*device));
   if (!device)
      goto error;

   device->fd        = fd;
   device->dev       = st.st_dev;
   device->handle_cb = cb;
   device->type      = type;

   strlcpy(device->devnode, devnode, sizeof(device->devnode));

   /* UDEV_INPUT_MOUSE may report in absolute coords too */
   if (type == UDEV_INPUT_MOUSE || type == UDEV_INPUT_TOUCHPAD )
   {
      if (ioctl(fd, EVIOCGABS(ABS_X), &absinfo) >= 0)
      {
         if (absinfo.minimum >= absinfo.maximum )
      	 {
            device->mouse.x_min = -1;
            device->mouse.x_max = -1;
         }
         else
         {
            device->mouse.x_min = absinfo.minimum;
            device->mouse.x_max = absinfo.maximum;
         }
      }

      if (ioctl(fd, EVIOCGABS(ABS_Y), &absinfo) >= 0)
      {
         if (absinfo.minimum >= absinfo.maximum )
         {
            device->mouse.y_min = -1;
            device->mouse.y_max = -1;
         }
	     else
         {
           device->mouse.y_min = absinfo.minimum;
           device->mouse.y_max = absinfo.maximum;
         }
      }
   }

   tmp = ( udev_input_device_t**)realloc(udev->devices,
         (udev->num_devices + 1) * sizeof(*udev->devices));

   if (!tmp)
      goto error;

   tmp[udev->num_devices++] = device;
   udev->devices            = tmp;

#if defined(HAVE_EPOLL)
   event.events             = EPOLLIN;
   event.data.ptr           = device;

   /* Shouldn't happen, but just check it. */
   if (epoll_ctl(udev->fd, EPOLL_CTL_ADD, fd, &event) < 0)
   {
      RARCH_ERR("Failed to add FD (%d) to epoll list (%s).\n",
            fd, strerror(errno));
   }
#elif defined(HAVE_KQUEUE)
   EV_SET(&event, fd, EVFILT_READ, EV_ADD, 0, 0, LISTENSOCKET);
   if (kevent(udev->fd, &event, 1, NULL, 0, NULL) == -1)
   {
      RARCH_ERR("Failed to add FD (%d) to kqueue list (%s).\n",
            fd, strerror(errno));
   }
#endif

   return true;

error:
   close(fd);
   if (device)
      free(device);

   return false;
}