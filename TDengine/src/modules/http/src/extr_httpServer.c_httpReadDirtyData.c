#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int fd; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
 scalar_t__ taosReadSocket (int,char*,int) ; 

void httpReadDirtyData(HttpContext *pContext) {
  int fd = pContext->fd;
  char data[1024] = {0};
  int  len = (int)taosReadSocket(fd, data, 1024);
  while (len >= sizeof(data)) {
    len = (int)taosReadSocket(fd, data, 1024);
  }
}