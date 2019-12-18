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

const char *sal_uinttos(int value)
{
 static char buf[64],buf2[64];
 char *tmp;
 int len=0;

 tmp=buf;

 while(value)
 {
  *tmp='0'+(value%10);
  len++;
  tmp++;
  value/=10;
 }

 tmp=buf2;
 while(len-- >= 0)
 {
  *tmp=buf[len];
  tmp++;
 }

 *tmp=0;
 return(buf2);
}