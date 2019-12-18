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
typedef  int curliocmd ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
#define  CURLIOCMD_RESTARTREAD 128 
 int /*<<< orphan*/  CURLIOE_FAILRESTART ; 
 int /*<<< orphan*/  CURLIOE_OK ; 
 int /*<<< orphan*/  CURLIOE_UNKNOWNCMD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static curlioerr my_ioctl(CURL *handle, curliocmd cmd, void *userp)
{
  int *fdp = (int *)userp;
  int fd = *fdp;

  (void)handle; /* not used in here */

  switch(cmd) {
  case CURLIOCMD_RESTARTREAD:
    /* mr libcurl kindly asks as to rewind the read data stream to start */
    if(-1 == lseek(fd, 0, SEEK_SET))
      /* couldn't rewind */
      return CURLIOE_FAILRESTART;

    break;

  default: /* ignore unknown commands */
    return CURLIOE_UNKNOWNCMD;
  }
  return CURLIOE_OK; /* success! */
}