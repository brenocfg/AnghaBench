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
typedef  scalar_t__ uint32_t ;
struct dirent {int dummy; } ;
struct TYPE_3__ {scalar_t__ data; scalar_t__* params; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 int /*<<< orphan*/  VC_FILESYS_READDIR ; 
 int /*<<< orphan*/  fs_host_direntbytestream_interp (struct dirent*,void*) ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

struct dirent *vc_filesys_readdir_r(void *dhandle, struct dirent *result)
{
   struct dirent *ret = NULL;

   if(lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = (uint32_t)dhandle;
      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, VC_FILESYS_READDIR, 4) == FILESERV_RESP_OK)
      {
         fs_host_direntbytestream_interp(result, (void *)vc_filesys_client.fileserv_msg.data);
         ret = result;
      }

      lock_release();
   }

   return ret;
}