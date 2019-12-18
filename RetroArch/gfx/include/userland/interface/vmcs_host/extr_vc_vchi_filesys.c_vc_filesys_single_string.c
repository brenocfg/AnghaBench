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
struct TYPE_3__ {scalar_t__* params; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 int FILESERV_MAX_DATA ; 
 scalar_t__ FILESERV_RESP_OK ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int vc_filesys_single_string(uint32_t param, const char *str, uint32_t fn, int return_param)
{
   int ret = -1;
   int len = strlen(str);

   if(len < FILESERV_MAX_DATA && lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = param;
      /* coverity[buffer_size_warning] - the length of str has already been checked */
      strncpy((char*)vc_filesys_client.fileserv_msg.data, str, FILESERV_MAX_DATA);

      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, fn, len+1+16) == FILESERV_RESP_OK)
      {
         if(return_param)
            ret = (int) vc_filesys_client.fileserv_msg.params[0];
         else
            ret = 0;
      }

      lock_release();
   }

   return ret;
}