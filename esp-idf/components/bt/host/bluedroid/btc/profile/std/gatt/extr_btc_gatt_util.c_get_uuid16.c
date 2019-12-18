#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  uuid32; int /*<<< orphan*/ * uuid128; int /*<<< orphan*/  uuid16; } ;
struct TYPE_5__ {scalar_t__ len; TYPE_1__ uu; } ;
typedef  TYPE_2__ tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int LEN_UUID_128 ; 
 scalar_t__ LEN_UUID_16 ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint16_t get_uuid16(tBT_UUID *p_uuid)
{
    if (p_uuid->len == LEN_UUID_16) {
        return p_uuid->uu.uuid16;
    } else if (p_uuid->len == LEN_UUID_128) {
        UINT16 u16;
        UINT8 *p = &p_uuid->uu.uuid128[LEN_UUID_128 - 4];
        STREAM_TO_UINT16(u16, p);
        return u16;
    } else { /* p_uuid->len == LEN_UUID_32 */
        return (UINT16) p_uuid->uu.uuid32;
    }
}