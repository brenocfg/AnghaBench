#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  open_handle; int /*<<< orphan*/  filesys_lock; scalar_t__ initialised; } ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__ vc_filesys_client ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int32_t lock_obtain (void) {
   int ret = -1;
   if(vc_filesys_client.initialised && vcos_mutex_lock(&vc_filesys_client.filesys_lock) == VCOS_SUCCESS) {
      vchi_service_use(vc_filesys_client.open_handle);
      ret = 0;
   }
   return ret;
}