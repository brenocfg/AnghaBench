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
struct zlib_trans_stream {int ex; } ;

/* Variables and functions */
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static bool zlib_deflate_define(void *data, const char *prop, uint32_t val)
{
   struct zlib_trans_stream *z = (struct zlib_trans_stream *) data;
   if (string_is_equal(prop, "level"))
   {
      if (z)
         z->ex = (int) val;
      return true;
   }
   return false;
}