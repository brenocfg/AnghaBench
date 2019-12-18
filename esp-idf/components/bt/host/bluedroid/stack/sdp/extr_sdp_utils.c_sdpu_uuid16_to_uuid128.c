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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int MAX_UUID_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sdp_base_uuid ; 

void sdpu_uuid16_to_uuid128(UINT16 uuid16, UINT8 *p_uuid128)
{
    UINT16 uuid16_bo;
    memset(p_uuid128, 0, 16);

    memcpy(p_uuid128, sdp_base_uuid, MAX_UUID_SIZE);
    uuid16_bo = ntohs(uuid16);
    memcpy(p_uuid128 + 2, &uuid16_bo, sizeof(uint16_t));
}