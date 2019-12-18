#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int int64_t ;
struct TYPE_6__ {void** params; } ;
struct TYPE_7__ {TYPE_2__ fileserv_msg; } ;
struct TYPE_5__ {int st_size; void* st_modtime; } ;
typedef  TYPE_1__ FSTAT_T ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 int /*<<< orphan*/  VC_FILESYS_FSTAT ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_4__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int vc_filesys_fstat(int fildes, FSTAT_T *buf)
{
   int success = -1;

   if (buf != NULL && lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = (uint32_t) fildes;
      if ( vchi_msg_stub(&vc_filesys_client.fileserv_msg, VC_FILESYS_FSTAT, 4) == FILESERV_RESP_OK )
      {
         buf->st_size = (int64_t)vc_filesys_client.fileserv_msg.params[0];          // LSB
         buf->st_size |= (int64_t)vc_filesys_client.fileserv_msg.params[1] << 32;    // MSB
         buf->st_modtime = (uint32_t)vc_filesys_client.fileserv_msg.params[2];
         // there's room for expansion here to pass across more elements of the structure if required...
         success = 0;
      }

      lock_release();
   }

   return success;
}