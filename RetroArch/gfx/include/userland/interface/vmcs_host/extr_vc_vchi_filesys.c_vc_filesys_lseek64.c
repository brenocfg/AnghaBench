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
typedef  void* uint32_t ;
typedef  int int64_t ;
struct TYPE_3__ {int* params; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 int /*<<< orphan*/  VC_FILESYS_LSEEK64 ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int64_t vc_filesys_lseek64(int fildes, int64_t offset, int whence)
{
   int64_t set = -1;

   if(lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = (uint32_t) fildes;
      vc_filesys_client.fileserv_msg.params[1] = (uint32_t) offset;        // LSB
      vc_filesys_client.fileserv_msg.params[2] = (uint32_t)(offset >> 32); // MSB
      vc_filesys_client.fileserv_msg.params[3] = (uint32_t) whence;

      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, VC_FILESYS_LSEEK64, 16) == FILESERV_RESP_OK)
      {
         set = vc_filesys_client.fileserv_msg.params[0];
         set += (int64_t)vc_filesys_client.fileserv_msg.params[1] << 32;
      }

      lock_release();
   }

   return set;
}