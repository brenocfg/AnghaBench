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
 int /*<<< orphan*/  printf (char*,int,size_t,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int _strlen_check(int linenumber, char *buf, size_t len)
{
  size_t buflen = strlen(buf);
  if(len != buflen) {
    /* they shouldn't differ */
    printf("sprintf strlen:%d failed:\nwe '%zu'\nsystem: '%zu'\n",
           linenumber, buflen, len);
    return 1;
  }
  return 0;
}