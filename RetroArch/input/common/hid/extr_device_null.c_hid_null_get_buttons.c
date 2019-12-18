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
typedef  int /*<<< orphan*/  input_bits_t ;
typedef  int /*<<< orphan*/  hid_null_instance_t ;

/* Variables and functions */

__attribute__((used)) static void hid_null_get_buttons(void *data, input_bits_t *state)
{
   hid_null_instance_t *instance = (hid_null_instance_t *)data;
   if (!instance)
      return;

   /* TODO: get buttons */
}