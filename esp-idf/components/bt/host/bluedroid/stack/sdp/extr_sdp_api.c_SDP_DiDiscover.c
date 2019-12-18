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
struct TYPE_4__ {int uuid16; } ;
struct TYPE_5__ {int len; TYPE_1__ uu; } ;
typedef  TYPE_2__ tSDP_UUID ;
typedef  int /*<<< orphan*/  tSDP_DISC_CMPL_CB ;
typedef  int /*<<< orphan*/  tSDP_DISCOVERY_DB ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int SDP_DI_DISC_FAILED ; 
 scalar_t__ SDP_InitDiscoveryDb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SDP_SUCCESS ; 
 scalar_t__ SDP_ServiceSearchRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UUID_SERVCLASS_PNP_INFORMATION ; 

UINT16 SDP_DiDiscover( BD_ADDR remote_device, tSDP_DISCOVERY_DB *p_db,
                       UINT32 len, tSDP_DISC_CMPL_CB *p_cb )
{
#if SDP_CLIENT_ENABLED == TRUE
    UINT16  result   = SDP_DI_DISC_FAILED;
    UINT16  num_uuids = 1;
    UINT16  di_uuid   = UUID_SERVCLASS_PNP_INFORMATION;

    /* build uuid for db init */
    tSDP_UUID init_uuid;
    init_uuid.len = 2;
    init_uuid.uu.uuid16 = di_uuid;

    if ( SDP_InitDiscoveryDb(p_db, len, num_uuids, &init_uuid, 0, NULL) ) {
        if ( SDP_ServiceSearchRequest(remote_device, p_db, p_cb) ) {
            result = SDP_SUCCESS;
        }
    }
    return result;
#else
    return SDP_DI_DISC_FAILED;
#endif
}