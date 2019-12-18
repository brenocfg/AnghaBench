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
typedef  scalar_t__ fattributes_t ;
struct TYPE_3__ {scalar_t__* params; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 int /*<<< orphan*/  FS_MAX_PATH ; 
 int /*<<< orphan*/  VC_FILESYS_GET_ATTR ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int vc_filesys_get_attr(const char *path, fattributes_t *attr)
{
   int success = -1;

   if(lock_obtain() == 0)
   {
      strncpy((char *)vc_filesys_client.fileserv_msg.data, path, FS_MAX_PATH);

      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, VC_FILESYS_GET_ATTR,
                        (int)(16+strlen((char *)vc_filesys_client.fileserv_msg.data)+1)) == FILESERV_RESP_OK)
      {
         success = 0;
         *attr = (fattributes_t) vc_filesys_client.fileserv_msg.params[0];
      }

      lock_release();
   }

   return success;
}