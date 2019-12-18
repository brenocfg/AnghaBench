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
 int sscanf (char*,char*,...) ; 
 scalar_t__ vc_gencmd_string_property (char*,char const*,char**,int*) ; 

int vc_gencmd_number_property(char *text, const char *property, int *number) {
   char *value, temp;
   int length, retval;
   if (vc_gencmd_string_property(text, property, &value, &length) == 0)
      return 0;
   temp = value[length];
   value[length] = 0;
   /* coverity[secure_coding] - this is not insecure */
   retval = sscanf(value, "0x%x", (unsigned int*)number);
   if (retval != 1)
      /* coverity[secure_coding] - this is not insecure */
      retval = sscanf(value, "%d", number);
   value[length] = temp;
   return retval;

}