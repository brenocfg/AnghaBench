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
struct TYPE_3__ {char* path_extension; char* path; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 int strlen (char*) ; 

__attribute__((used)) static void vc_uri_set_path_extension(VC_URI_PARTS_T *p_uri)
{
   char *end;

   if (!p_uri)
      return;

   p_uri->path_extension = NULL;

   if (!p_uri->path)
      return;

   /* Look for the magic dot */
   for (end = p_uri->path + strlen(p_uri->path); *end != '.'; end--)
      if (end == p_uri->path || *end == '/' || *end == '\\')
         return;

   p_uri->path_extension = end + 1;
}