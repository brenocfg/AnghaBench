#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  curlioerr ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURLIOCMD_RESTARTREAD ; 
 int /*<<< orphan*/  CURLIOE_OK ; 
 int /*<<< orphan*/  CURLIOE_UNKNOWNCMD ; 
 scalar_t__ current_offset ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static curlioerr ioctl_callback(CURL *handle, int cmd, void *clientp)
{
  (void)clientp;
  if(cmd == CURLIOCMD_RESTARTREAD) {
    printf("APPLICATION: received a CURLIOCMD_RESTARTREAD request\n");
    printf("APPLICATION: ** REWINDING! **\n");
    current_offset = 0;
    return CURLIOE_OK;
  }
  (void)handle;
  return CURLIOE_UNKNOWNCMD;
}