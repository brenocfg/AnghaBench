#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VC_PACKETIZER_REGISTRY_ENTRY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* registry ; 

void vc_packetizer_register(VC_PACKETIZER_REGISTRY_ENTRY_T *entry)
{
   LOG_DEBUG(0, "registering packetizer %s", entry->name);
   entry->next = registry;
   registry = entry;
}