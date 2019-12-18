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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  logmsg (char*,char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,unsigned char) ; 

__attribute__((used)) static void loghex(unsigned char *buffer, ssize_t len)
{
  char data[1200];
  ssize_t i;
  unsigned char *ptr = buffer;
  char *optr = data;
  ssize_t width = 0;
  int left = sizeof(data);

  for(i = 0; i<len && (left >= 0); i++) {
    msnprintf(optr, left, "%02x", ptr[i]);
    width += 2;
    optr += 2;
    left -= 2;
  }
  if(width)
    logmsg("'%s'", data);
}