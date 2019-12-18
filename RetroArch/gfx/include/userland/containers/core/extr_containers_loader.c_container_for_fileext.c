#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* container; scalar_t__ extension; } ;

/* Variables and functions */
 TYPE_1__* extension_container_mapping ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 

__attribute__((used)) static const char* container_for_fileext(const char *fileext)
{
   int i;

   for( i = 0; fileext && extension_container_mapping[i].extension; i++ )
   {
      if (!strcasecmp( fileext, extension_container_mapping[i].extension ))
         return extension_container_mapping[i].container;
   }

   return fileext;
}