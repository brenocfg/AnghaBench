#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {TYPE_2__ stat; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ iox_dirent_t ;
struct TYPE_10__ {size_t current_folder_position; size_t items; TYPE_1__* FileEntry; } ;
struct TYPE_7__ {scalar_t__ dircheck; int /*<<< orphan*/  filename; } ;
typedef  TYPE_4__ DescriptorTranslation ;

/* Variables and functions */
 int /*<<< orphan*/  FIO_S_IFDIR ; 
 int /*<<< orphan*/  FIO_S_IFREG ; 
 TYPE_4__* __ps2_fd_grab (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fileXioCDDread(int fd, iox_dirent_t *dirent)
{
   DescriptorTranslation *descriptor = __ps2_fd_grab(fd);

   if (descriptor && descriptor->current_folder_position < descriptor->items) {
      strcpy(dirent->name, descriptor->FileEntry[descriptor->current_folder_position].filename);
      if (descriptor->FileEntry[descriptor->current_folder_position].dircheck) {
         dirent->stat.mode = FIO_S_IFDIR;
      } else {
         dirent->stat.mode = FIO_S_IFREG;
      }
      descriptor->current_folder_position++;
   } else {
      descriptor->current_folder_position = 0;
      return 0;
   }

   return 1;
}