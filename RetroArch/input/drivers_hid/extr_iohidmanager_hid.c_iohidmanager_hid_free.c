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
struct TYPE_4__ {int /*<<< orphan*/  slots; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  iohidmanager_hid_manager_free (TYPE_1__*) ; 
 int /*<<< orphan*/  pad_connection_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iohidmanager_hid_free(const void *data)
{
   iohidmanager_hid_t *hid_apple = (iohidmanager_hid_t*)data;

   if (!hid_apple || !hid_apple->ptr)
      return;

   pad_connection_destroy(hid_apple->slots);
   iohidmanager_hid_manager_free(hid_apple);

   if (hid_apple)
      free(hid_apple);
}