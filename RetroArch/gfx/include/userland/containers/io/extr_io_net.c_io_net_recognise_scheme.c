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
struct TYPE_3__ {char* scheme; int is_udp; } ;

/* Variables and functions */
 size_t countof (TYPE_1__*) ; 
 TYPE_1__* recognised_schemes ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool io_net_recognise_scheme(const char *uri, bool *is_udp)
{
   size_t ii;
   const char *scheme;

   if (!uri)
      return false;

   for (ii = 0; ii < countof(recognised_schemes); ii++)
   {
      scheme = recognised_schemes[ii].scheme;
      if (strncmp(scheme, uri, strlen(scheme)) == 0)
      {
         *is_udp = recognised_schemes[ii].is_udp;
         return true;
      }
   }

   return false;
}