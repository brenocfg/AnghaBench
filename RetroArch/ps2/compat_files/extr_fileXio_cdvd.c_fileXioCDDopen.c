#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  FileEntry; int /*<<< orphan*/  items; scalar_t__ current_folder_position; } ;
typedef  TYPE_1__ DescriptorTranslation ;

/* Variables and functions */
 int __ps2_acquire_descriptor () ; 
 TYPE_1__* __ps2_fd_grab (int) ; 
 int /*<<< orphan*/  listcdvd (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ prepareCDVD () ; 

__attribute__((used)) static int fileXioCDDopen(const char *name)
{
   int fd = -1;
   if (prepareCDVD()){
      fd = __ps2_acquire_descriptor();
      DescriptorTranslation *descriptor = __ps2_fd_grab(fd);
      descriptor->current_folder_position = 0;
      descriptor->items = listcdvd(name, descriptor->FileEntry);
   }
   return fd;
}