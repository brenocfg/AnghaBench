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

/* Variables and functions */
 int /*<<< orphan*/  dlog (char*,char*,int,char*) ; 
 int innetgr (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* opt_host ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
f_netgrp(char *arg)
{
  int status;
  char *ptr, *nhost;

  if ((ptr = strchr(arg, ',')) != NULL) {
    *ptr = '\0';
    nhost = ptr + 1;
  } else {
    nhost = opt_host;
  }
  status = innetgr(arg, nhost, NULL, NULL);
  dlog("netgrp = %s status = %d host = %s", arg, status, nhost);
  if (ptr)
    *ptr = ',';
  return status;
}