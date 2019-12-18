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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

char *mmal_4cc_to_string(char *buf, size_t len, uint32_t fourcc)
{
   char *src = (char*)&fourcc;
   vcos_assert(len >= 5);
   if (len < 5)
   {
      buf[0] = '\0';
   }
   else if (fourcc)
   {
      memcpy(buf, src, 4);
      buf[4] = '\0';
   }
   else
   {
      snprintf(buf, len, "<0>");
   }
   return buf;
}