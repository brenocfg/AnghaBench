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
struct TYPE_3__ {long num; long den; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_parse_rational(MMAL_RATIONAL_T *dest, const char *str)
{
   MMAL_STATUS_T ret;
   char *endptr;
   long num, den = 1;
   num = strtoul(str, &endptr, 0);
   if (endptr[0] == '\0')
   {
      /* that's it */
      ret = MMAL_SUCCESS;
   }
   else if (endptr[0] == '/')
   {
      den = strtoul(endptr+1, &endptr, 0);
      if (endptr[0] == '\0')
         ret = MMAL_SUCCESS;
      else
         ret = MMAL_EINVAL;
   }
   else
   {
      ret = MMAL_EINVAL;
   }
   dest->num = num;
   dest->den = den;
   return ret;
}