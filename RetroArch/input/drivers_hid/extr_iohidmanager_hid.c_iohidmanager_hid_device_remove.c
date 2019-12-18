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
struct iohidmanager_hid_adapter {size_t slot; struct iohidmanager_hid_adapter* next; struct iohidmanager_hid_adapter* buttons; struct iohidmanager_hid_adapter* axes; struct iohidmanager_hid_adapter* hats; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * slots; int /*<<< orphan*/ * axes; scalar_t__* buttons; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;
typedef  struct iohidmanager_hid_adapter apple_input_rec_t ;
typedef  int /*<<< orphan*/  IOReturn ;

/* Variables and functions */
 size_t MAX_USERS ; 
 int /*<<< orphan*/  free (struct iohidmanager_hid_adapter*) ; 
 scalar_t__ hid_driver_get_data () ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad_connection_pad_deinit (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void iohidmanager_hid_device_remove(void *data,
      IOReturn result, void* sender)
{
   struct iohidmanager_hid_adapter *adapter =
      (struct iohidmanager_hid_adapter*)data;
   iohidmanager_hid_t *hid = (iohidmanager_hid_t*)
      hid_driver_get_data();

   if (hid && adapter && (adapter->slot < MAX_USERS))
   {
      input_autoconfigure_disconnect(adapter->slot, adapter->name);

      hid->buttons[adapter->slot] = 0;
      memset(hid->axes[adapter->slot], 0, sizeof(hid->axes));

      pad_connection_pad_deinit(&hid->slots[adapter->slot], adapter->slot);
   }

   if (adapter)
   {
      apple_input_rec_t* tmp = NULL;
      while (adapter->hats != NULL)
      {
          tmp           = adapter->hats;
          adapter->hats = adapter->hats->next;
          free(tmp);
      }

      while (adapter->axes != NULL)
      {
          tmp           = adapter->axes;
          adapter->axes = adapter->axes->next;
          free(tmp);
      }

      while (adapter->buttons != NULL)
      {
          tmp              = adapter->buttons;
          adapter->buttons = adapter->buttons->next;
          free(tmp);
      }
      free(adapter);
   }
}