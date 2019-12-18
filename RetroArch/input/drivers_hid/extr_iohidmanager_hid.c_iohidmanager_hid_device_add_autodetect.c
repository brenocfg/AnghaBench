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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,char const*) ; 
 int /*<<< orphan*/  input_autoconfigure_connect (char const*,int /*<<< orphan*/ *,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iohidmanager_hid_device_add_autodetect(unsigned idx,
      const char *device_name, const char *driver_name,
      uint16_t dev_vid, uint16_t dev_pid)
{
   input_autoconfigure_connect(
         device_name,
         NULL,
         driver_name,
         idx,
         dev_vid,
         dev_pid
         );

   RARCH_LOG("Port %d: %s.\n", idx, device_name);
}