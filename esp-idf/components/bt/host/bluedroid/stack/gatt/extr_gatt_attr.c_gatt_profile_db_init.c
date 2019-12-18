#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_15__ {int attr_max_len; int attr_len; int* attr_val; } ;
typedef  TYPE_4__ tGATT_ATTR_VAL ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  uuid16; int /*<<< orphan*/  uuid128; } ;
struct TYPE_16__ {TYPE_3__ member_1; int /*<<< orphan*/  member_0; TYPE_1__ uu; } ;
typedef  TYPE_5__ tBT_UUID ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_13__ {int /*<<< orphan*/  handle; scalar_t__ service_change; int /*<<< orphan*/  uuid; } ;
struct TYPE_17__ {int /*<<< orphan*/  gatt_if; int /*<<< orphan*/  handle_of_h_r; TYPE_2__ gattp_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GATTP_MAX_ATTR_NUM ; 
 int /*<<< orphan*/  GATTP_TRANSPORT_SUPPORTED ; 
 int /*<<< orphan*/  GATTS_AddCharDescriptor (int /*<<< orphan*/ ,int,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GATTS_AddCharacteristic (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GATTS_CreateService (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATTS_StartService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_CHAR_PROP_BIT_INDICATE ; 
 int GATT_PERM_READ ; 
 int GATT_PERM_WRITE ; 
 int /*<<< orphan*/  GATT_Register (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GATT_StartIf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GATT_UUID_CHAR_CLIENT_CONFIG ; 
 int /*<<< orphan*/  GATT_UUID_GATT_SRV_CHGD ; 
 int /*<<< orphan*/  LEN_UUID_128 ; 
 int /*<<< orphan*/  LEN_UUID_16 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UUID_SERVCLASS_GATT_SERVER ; 
 TYPE_6__ gatt_cb ; 
 int /*<<< orphan*/  gatt_profile_cback ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void gatt_profile_db_init (void)
{
    tBT_UUID          app_uuid = {LEN_UUID_128, {0}};
    tBT_UUID          uuid = {LEN_UUID_16, {UUID_SERVCLASS_GATT_SERVER}};
    UINT16            service_handle = 0;
    tGATT_STATUS      status;

    /* Fill our internal UUID with a fixed pattern 0x81 */
    memset (&app_uuid.uu.uuid128, 0x81, LEN_UUID_128);


    /* Create a GATT profile service */
    gatt_cb.gatt_if = GATT_Register(&app_uuid, &gatt_profile_cback);
    GATT_StartIf(gatt_cb.gatt_if);

    service_handle = GATTS_CreateService (gatt_cb.gatt_if , &uuid, 0, GATTP_MAX_ATTR_NUM, TRUE);
    GATT_TRACE_DEBUG ("GATTS_CreateService:  handle of service handle%x", service_handle);

    /* add Service Changed characteristic
    */
    uuid.uu.uuid16 = gatt_cb.gattp_attr.uuid = GATT_UUID_GATT_SRV_CHGD;
    gatt_cb.gattp_attr.service_change = 0;
    gatt_cb.gattp_attr.handle   =
    gatt_cb.handle_of_h_r       = GATTS_AddCharacteristic(service_handle, &uuid, 0, GATT_CHAR_PROP_BIT_INDICATE,
    												    NULL, NULL);

    GATT_TRACE_DEBUG ("gatt_profile_db_init:  handle of service changed%d\n",
                      gatt_cb.handle_of_h_r);
    
    tBT_UUID descr_uuid = {LEN_UUID_16, {GATT_UUID_CHAR_CLIENT_CONFIG}};
    uint8_t ccc_value[2] ={ 0x00, 0x00};

    tGATT_ATTR_VAL  attr_val = {
        .attr_max_len = sizeof(UINT16),
        .attr_len = sizeof(UINT16),
        .attr_val = ccc_value,
    };

    GATTS_AddCharDescriptor (service_handle, GATT_PERM_READ | GATT_PERM_WRITE , &descr_uuid, &attr_val, NULL);
    /* start service
    */
    status = GATTS_StartService (gatt_cb.gatt_if, service_handle, GATTP_TRANSPORT_SUPPORTED );

#if (CONFIG_BT_STACK_NO_LOG)
    (void) status;
#endif

    GATT_TRACE_DEBUG ("gatt_profile_db_init:  gatt_if=%d   start status%d\n",
                      gatt_cb.gatt_if,  status);
}