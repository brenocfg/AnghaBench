#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ u16; scalar_t__ u32; scalar_t__ array; } ;
struct TYPE_10__ {TYPE_2__ v; } ;
struct TYPE_11__ {TYPE_3__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
struct TYPE_8__ {scalar_t__ uuid16; scalar_t__ uuid32; int /*<<< orphan*/  uuid128; } ;
struct TYPE_12__ {scalar_t__ len; TYPE_1__ uu; } ;
typedef  TYPE_5__ tBT_UUID ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_UUID_SIZE ; 
 scalar_t__ SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

BOOLEAN sdpu_compare_uuid_with_attr (tBT_UUID *p_btuuid, tSDP_DISC_ATTR *p_attr)
{
    UINT16      attr_len = SDP_DISC_ATTR_LEN (p_attr->attr_len_type);

    /* Since both UUIDs are compressed, lengths must match  */
    if (p_btuuid->len != attr_len) {
        return (FALSE);
    }

    if (p_btuuid->len == 2) {
        return (BOOLEAN)(p_btuuid->uu.uuid16 == p_attr->attr_value.v.u16);
    } else if (p_btuuid->len == 4) {
        return (BOOLEAN)(p_btuuid->uu.uuid32 == p_attr->attr_value.v.u32);
    }
    /* coverity[overrun-buffer-arg] */
    /*
       Event overrun-buffer-arg: Overrun of static array "&p_attr->attr_value.v.array" of size 4 bytes by passing it to a function which indexes it with argument "16U" at byte position 15
       FALSE-POSITIVE error from Coverity test tool. Please do NOT remove following comment.
       False-positive: SDP uses scratch buffer to hold the attribute value.
       The actual size of tSDP_DISC_ATVAL does not matter.
       If the array size in tSDP_DISC_ATVAL is increase, we would increase the system RAM usage unnecessarily
    */
    else if (!memcmp (p_btuuid->uu.uuid128, (void *) p_attr->attr_value.v.array, MAX_UUID_SIZE)) {
        return (TRUE);
    }

    return (FALSE);
}