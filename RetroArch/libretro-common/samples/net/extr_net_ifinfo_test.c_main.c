#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int size; TYPE_1__* entries; } ;
typedef  TYPE_2__ net_ifinfo_t ;
struct TYPE_5__ {char* name; char* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  net_ifinfo_free (TYPE_2__*) ; 
 int /*<<< orphan*/  net_ifinfo_new (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

int main(int argc, const char *argv[])
{
   unsigned k              = 0;
   net_ifinfo_t list;

   if (!net_ifinfo_new(&list))
      return -1;

   for (k = 0; k < list.size; k++)
   {
      printf("%s:%s\n", list.entries[k].name, list.entries[k].host);
   }

   net_ifinfo_free(&list);

   return 0;
}