#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_8__ {int LinkType; int LinkSpeed; } ;
struct TYPE_7__ {int Length; scalar_t__ Data; int /*<<< orphan*/  Oid; } ;
typedef  TYPE_1__* PPACKET_OID_DATA ;
typedef  int /*<<< orphan*/  PACKET_OID_DATA ;
typedef  TYPE_2__ NetType ;
typedef  int /*<<< orphan*/  LPADAPTER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GMEM_MOVEABLE ; 
 int GMEM_ZEROINIT ; 
 TYPE_1__* GlobalAllocPtr (int,int) ; 
 int /*<<< orphan*/  GlobalFreePtr (TYPE_1__*) ; 
 int /*<<< orphan*/  ODS (char*) ; 
 int /*<<< orphan*/  ODSEx (char*,int) ; 
 int /*<<< orphan*/  OID_GEN_LINK_SPEED ; 
 int /*<<< orphan*/  OID_GEN_MEDIA_IN_USE ; 
 int /*<<< orphan*/  PacketRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOLEAN PacketGetLinkLayerFromRegistry(LPADAPTER AdapterObject, NetType *type)
{
    BOOLEAN    Status;
    ULONG      IoCtlBufferLength=(sizeof(PACKET_OID_DATA)+sizeof(ULONG)-1);
    PPACKET_OID_DATA  OidData;

    OidData=GlobalAllocPtr(GMEM_MOVEABLE | GMEM_ZEROINIT,IoCtlBufferLength);
    if (OidData == NULL) {
        ODS("PacketGetLinkLayerFromRegistry failed\n");
        return FALSE;
    }
	//get the link-layer type
    OidData->Oid = OID_GEN_MEDIA_IN_USE;
    OidData->Length = sizeof (ULONG);
    Status = PacketRequest(AdapterObject,FALSE,OidData);
    type->LinkType=*((UINT*)OidData->Data);

	//get the link-layer speed
    OidData->Oid = OID_GEN_LINK_SPEED;
    OidData->Length = sizeof (ULONG);
    Status = PacketRequest(AdapterObject,FALSE,OidData);
	type->LinkSpeed=*((UINT*)OidData->Data)*100;
    GlobalFreePtr (OidData);

	ODSEx("Media:%d\n",type->LinkType);
	ODSEx("Speed=%d\n",type->LinkSpeed);

    return Status;
}