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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static curlioerr ioctlcallback(CURL *handle,
                               int cmd,
                               void *clientp)
{
  int *counter = (int *)clientp;
  (void)handle; /* unused */
  if(cmd == CURLIOCMD_RESTARTREAD) {
    fprintf(stderr, "REWIND!\n");
    *counter = 0; /* clear counter to make the read callback restart */
  }
  return CURLIOE_OK;
}