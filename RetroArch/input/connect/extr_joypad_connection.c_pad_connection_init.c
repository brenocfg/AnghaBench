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
struct TYPE_4__ {int connected; int /*<<< orphan*/ * data; int /*<<< orphan*/ * iface; } ;
typedef  TYPE_1__ joypad_connection_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  RARCH_WARN (char*,unsigned int,unsigned int) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  set_end_of_list (TYPE_1__*,unsigned int) ; 

joypad_connection_t *pad_connection_init(unsigned pads)
{
   unsigned i;
   joypad_connection_t *joyconn;

   if(pads > MAX_USERS)
   {
     RARCH_WARN("[joypad] invalid number of pads requested (%d), using default (%d)\n",
      pads, MAX_USERS);
     pads = MAX_USERS;
   }

   joyconn = (joypad_connection_t*)calloc(pads+1, sizeof(joypad_connection_t));

   if (!joyconn)
      return NULL;

   for (i = 0; i < pads; i++)
   {
      joypad_connection_t *conn = (joypad_connection_t*)&joyconn[i];

      conn->connected           = false;
      conn->iface               = NULL;
      conn->data                = NULL;
   }

   set_end_of_list(joyconn, pads);

   return joyconn;
}