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
typedef  int int64_t ;
struct TYPE_3__ {int* params; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 int /*<<< orphan*/  FS_MAX_PATH ; 
 int /*<<< orphan*/  VC_FILESYS_FREESPACE64 ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int64_t vc_filesys_freespace64(const char *path)
{
   int64_t freespace = -1LL;

   if(lock_obtain() == 0)
   {
      strncpy((char *)vc_filesys_client.fileserv_msg.data, path, FS_MAX_PATH);

      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, VC_FILESYS_FREESPACE64,
                        (int)(16+strlen((char *)vc_filesys_client.fileserv_msg.data)+1)) == FILESERV_RESP_OK)
      {
         freespace = vc_filesys_client.fileserv_msg.params[0];
         freespace += (int64_t)vc_filesys_client.fileserv_msg.params[1] << 32;
      }

      lock_release();
   }

   return freespace;
}