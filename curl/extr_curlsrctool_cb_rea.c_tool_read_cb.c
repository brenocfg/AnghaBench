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
struct InStruct {TYPE_1__* config; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  readbusy; } ;

/* Variables and functions */
 size_t CURL_READFUNC_PAUSE ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ errno ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t) ; 

size_t tool_read_cb(void *buffer, size_t sz, size_t nmemb, void *userdata)
{
  ssize_t rc;
  struct InStruct *in = userdata;

  rc = read(in->fd, buffer, sz*nmemb);
  if(rc < 0) {
    if(errno == EAGAIN) {
      errno = 0;
      in->config->readbusy = TRUE;
      return CURL_READFUNC_PAUSE;
    }
    /* since size_t is unsigned we can't return negative values fine */
    rc = 0;
  }
  in->config->readbusy = FALSE;
  return (size_t)rc;
}