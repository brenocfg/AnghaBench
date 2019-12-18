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
struct TYPE_3__ {int /*<<< orphan*/  slots; } ;
typedef  TYPE_1__ btstack_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_set_inquiry_state (int) ; 
 int /*<<< orphan*/  btstack_set_poweron (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pad_connection_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btstack_hid_free(const void *data)
{
   btstack_hid_t *hid = (btstack_hid_t*)data;

   if (!hid)
      return;

   pad_connection_destroy(hid->slots);
   btpad_set_inquiry_state(true);
   btstack_set_poweron(false);

   if (hid)
      free(hid);
}