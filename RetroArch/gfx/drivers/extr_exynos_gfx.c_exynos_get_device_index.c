#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* drmVersionPtr ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  drmFreeVersion (TYPE_1__*) ; 
 TYPE_1__* drmGetVersion (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int exynos_get_device_index(void)
{
   drmVersionPtr ver;
   char buf[32]       = {0};
   int index          = 0;
   bool found         = false;

   while (!found)
   {
      int fd;

      snprintf(buf, sizeof(buf), "/dev/dri/card%d", index);

      fd = open(buf, O_RDWR);
      if (fd < 0) break;

      ver = drmGetVersion(fd);

      if (string_is_equal(ver->name, "exynos"))
         found = true;
      else
         ++index;

      drmFreeVersion(ver);
      close(fd);
   }

   if (!found)
      return -1;
   return index;
}