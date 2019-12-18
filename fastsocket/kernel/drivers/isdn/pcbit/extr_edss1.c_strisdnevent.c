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
typedef  scalar_t__ ushort ;
struct isdn_event_desc {scalar_t__ ev; char* desc; } ;

/* Variables and functions */
 struct isdn_event_desc* isdn_event_table ; 

char * strisdnevent(ushort ev)
{
  struct isdn_event_desc * entry;
 
  for (entry = isdn_event_table; entry->ev; entry++)
    if (entry->ev == ev)
      break;

  return entry->desc;
}