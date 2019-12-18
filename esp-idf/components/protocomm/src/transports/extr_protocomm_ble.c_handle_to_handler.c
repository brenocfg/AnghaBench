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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int g_nu_lookup_count; TYPE_1__* g_nu_lookup; } ;
struct TYPE_3__ {char const* name; int /*<<< orphan*/  const* uuid128; } ;

/* Variables and functions */
 TYPE_2__* protoble_internal ; 
 int /*<<< orphan*/ * simple_ble_get_uuid128 (int /*<<< orphan*/ ) ; 
 scalar_t__* uuid128_to_16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *handle_to_handler(uint16_t handle)
{
    const uint8_t *uuid128 = simple_ble_get_uuid128(handle);
    if (!uuid128) {
        return NULL;
    }
    for (int i = 0; i < protoble_internal->g_nu_lookup_count; i++) {
        if (*uuid128_to_16(protoble_internal->g_nu_lookup[i].uuid128) == *uuid128_to_16(uuid128)) {
            return protoble_internal->g_nu_lookup[i].name;
        }
    }
    return NULL;
}