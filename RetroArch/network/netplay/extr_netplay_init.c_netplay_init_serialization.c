#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int size; } ;
typedef  TYPE_2__ retro_ctx_size_info_t ;
struct TYPE_8__ {int state_size; unsigned int buffer_size; int zbuffer_size; int /*<<< orphan*/  quirks; int /*<<< orphan*/ * zbuffer; TYPE_1__* buffer; } ;
typedef  TYPE_3__ netplay_t ;
struct TYPE_6__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_QUIRK_NO_SAVESTATES ; 
 int /*<<< orphan*/  NETPLAY_QUIRK_NO_TRANSMISSION ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  core_serialize_size (TYPE_2__*) ; 

bool netplay_init_serialization(netplay_t *netplay)
{
   unsigned i;
   retro_ctx_size_info_t info;

   if (netplay->state_size)
      return true;

   core_serialize_size(&info);

   if (!info.size)
      return false;

   netplay->state_size = info.size;

   for (i = 0; i < netplay->buffer_size; i++)
   {
      netplay->buffer[i].state = calloc(netplay->state_size, 1);

      if (!netplay->buffer[i].state)
      {
         netplay->quirks |= NETPLAY_QUIRK_NO_SAVESTATES;
         return false;
      }
   }

   netplay->zbuffer_size = netplay->state_size * 2;
   netplay->zbuffer = (uint8_t *) calloc(netplay->zbuffer_size, 1);
   if (!netplay->zbuffer)
   {
      netplay->quirks |= NETPLAY_QUIRK_NO_TRANSMISSION;
      netplay->zbuffer_size = 0;
      return false;
   }

   return true;
}