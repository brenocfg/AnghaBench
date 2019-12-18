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
typedef  int u32 ;
struct obj_mlmeex {int id; int state; int code; int size; } ;
struct obj_mlme {int id; int state; int code; } ;
struct obj_frequencies {int nr; int* mhz; } ;
struct obj_buffer {int size; int addr; } ;
struct obj_bsslist {int nr; int /*<<< orphan*/ * bsslist; } ;
struct obj_bss {int age; int channel; int capinfo; int rates; int basic_rates; } ;
struct obj_attachment {int id; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OID_TYPE_ADDR 139 
#define  OID_TYPE_ATTACH 138 
#define  OID_TYPE_BSS 137 
#define  OID_TYPE_BSSLIST 136 
#define  OID_TYPE_BUFFER 135 
#define  OID_TYPE_FREQUENCIES 134 
#define  OID_TYPE_KEY 133 
#define  OID_TYPE_MLME 132 
#define  OID_TYPE_MLMEEX 131 
#define  OID_TYPE_RAW 130 
#define  OID_TYPE_SSID 129 
#define  OID_TYPE_U32 128 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void
mgt_cpu_to_le(int type, void *data)
{
	switch (type) {
	case OID_TYPE_U32:
		*(u32 *) data = cpu_to_le32(*(u32 *) data);
		break;
	case OID_TYPE_BUFFER:{
			struct obj_buffer *buff = data;
			buff->size = cpu_to_le32(buff->size);
			buff->addr = cpu_to_le32(buff->addr);
			break;
		}
	case OID_TYPE_BSS:{
			struct obj_bss *bss = data;
			bss->age = cpu_to_le16(bss->age);
			bss->channel = cpu_to_le16(bss->channel);
			bss->capinfo = cpu_to_le16(bss->capinfo);
			bss->rates = cpu_to_le16(bss->rates);
			bss->basic_rates = cpu_to_le16(bss->basic_rates);
			break;
		}
	case OID_TYPE_BSSLIST:{
			struct obj_bsslist *list = data;
			int i;
			list->nr = cpu_to_le32(list->nr);
			for (i = 0; i < list->nr; i++)
				mgt_cpu_to_le(OID_TYPE_BSS, &list->bsslist[i]);
			break;
		}
	case OID_TYPE_FREQUENCIES:{
			struct obj_frequencies *freq = data;
			int i;
			freq->nr = cpu_to_le16(freq->nr);
			for (i = 0; i < freq->nr; i++)
				freq->mhz[i] = cpu_to_le16(freq->mhz[i]);
			break;
		}
	case OID_TYPE_MLME:{
			struct obj_mlme *mlme = data;
			mlme->id = cpu_to_le16(mlme->id);
			mlme->state = cpu_to_le16(mlme->state);
			mlme->code = cpu_to_le16(mlme->code);
			break;
		}
	case OID_TYPE_MLMEEX:{
			struct obj_mlmeex *mlme = data;
			mlme->id = cpu_to_le16(mlme->id);
			mlme->state = cpu_to_le16(mlme->state);
			mlme->code = cpu_to_le16(mlme->code);
			mlme->size = cpu_to_le16(mlme->size);
			break;
		}
	case OID_TYPE_ATTACH:{
			struct obj_attachment *attach = data;
			attach->id = cpu_to_le16(attach->id);
			attach->size = cpu_to_le16(attach->size);
			break;
	}
	case OID_TYPE_SSID:
	case OID_TYPE_KEY:
	case OID_TYPE_ADDR:
	case OID_TYPE_RAW:
		break;
	default:
		BUG();
	}
}