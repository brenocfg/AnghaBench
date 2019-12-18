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
struct TYPE_3__ {int value; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ string_pair_t ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ vcos_strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T parse_enum(int *dest, string_pair_t *pairs, size_t n_pairs, const char *str)
{
   size_t i;
   for (i=0; i<n_pairs; i++)
   {
      if (vcos_strcasecmp(str, pairs[i].string) == 0)
      {
         *dest = pairs[i].value;
         return MMAL_SUCCESS;
      }
   }
   return MMAL_EINVAL;
}