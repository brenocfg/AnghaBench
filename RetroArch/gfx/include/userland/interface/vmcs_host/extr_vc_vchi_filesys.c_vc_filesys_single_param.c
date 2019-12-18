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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * params; } ;
struct TYPE_4__ {TYPE_1__ fileserv_msg; } ;

/* Variables and functions */
 scalar_t__ FILESERV_RESP_OK ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 TYPE_2__ vc_filesys_client ; 
 scalar_t__ vchi_msg_stub (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vc_filesys_single_param(uint32_t param, uint32_t fn)
{
   int success = -1;

   if(lock_obtain() == 0)
   {
      vc_filesys_client.fileserv_msg.params[0] = param;
      if (vchi_msg_stub(&vc_filesys_client.fileserv_msg, fn, 4) == FILESERV_RESP_OK)
         success = 0;

      lock_release();
   }

   return success;
}