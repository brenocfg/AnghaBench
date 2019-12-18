#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pad_list; } ;
struct TYPE_3__ {int connected; } ;

/* Variables and functions */
 TYPE_2__ hid_instance ; 
 int /*<<< orphan*/  input_pad_connect (int,int /*<<< orphan*/ *) ; 
 int pad_connection_find_vacant_pad (TYPE_1__*) ; 
 int /*<<< orphan*/  wpad_driver ; 
 int /*<<< orphan*/  wpad_poll () ; 
 int wpad_ready ; 

__attribute__((used)) static bool wpad_init(void *data)
{
   int slot = pad_connection_find_vacant_pad(hid_instance.pad_list);
   if(slot < 0)
      return false;

   hid_instance.pad_list[slot].connected = true;
   input_pad_connect(slot, &wpad_driver);
   wpad_poll();
   wpad_ready = true;

   return true;
}