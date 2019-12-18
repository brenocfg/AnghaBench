#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ TupleDataLen; scalar_t__ TupleDataMax; int TupleCode; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_25__ {int /*<<< orphan*/  format; int /*<<< orphan*/  org; int /*<<< orphan*/  vers_2; int /*<<< orphan*/  device_geo; int /*<<< orphan*/  cftable_entry; int /*<<< orphan*/  config; int /*<<< orphan*/  funce; int /*<<< orphan*/  funcid; int /*<<< orphan*/  manfid; int /*<<< orphan*/  jedec; int /*<<< orphan*/  altstr; int /*<<< orphan*/  version_1; int /*<<< orphan*/  longlink_mfc; int /*<<< orphan*/  longlink; int /*<<< orphan*/  checksum; int /*<<< orphan*/  cftable_entry_cb; int /*<<< orphan*/  bar; int /*<<< orphan*/  device; } ;
typedef  TYPE_2__ cisparse_t ;

/* Variables and functions */
#define  CISTPL_ALTSTR 153 
#define  CISTPL_BAR 152 
#define  CISTPL_CFTABLE_ENTRY 151 
#define  CISTPL_CFTABLE_ENTRY_CB 150 
#define  CISTPL_CHECKSUM 149 
#define  CISTPL_CONFIG 148 
#define  CISTPL_CONFIG_CB 147 
#define  CISTPL_DEVICE 146 
#define  CISTPL_DEVICE_A 145 
#define  CISTPL_DEVICE_GEO 144 
#define  CISTPL_DEVICE_GEO_A 143 
#define  CISTPL_FORMAT 142 
#define  CISTPL_FORMAT_A 141 
#define  CISTPL_FUNCE 140 
#define  CISTPL_FUNCID 139 
#define  CISTPL_JEDEC_A 138 
#define  CISTPL_JEDEC_C 137 
#define  CISTPL_LINKTARGET 136 
#define  CISTPL_LONGLINK_A 135 
#define  CISTPL_LONGLINK_C 134 
#define  CISTPL_LONGLINK_MFC 133 
#define  CISTPL_MANFID 132 
#define  CISTPL_NO_LINK 131 
#define  CISTPL_ORG 130 
#define  CISTPL_VERS_1 129 
#define  CISTPL_VERS_2 128 
 int EINVAL ; 
 int /*<<< orphan*/  __cs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int parse_altstr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_bar (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_cftable_entry (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_cftable_entry_cb (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_checksum (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_config_cb (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_device (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_device_geo (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_format (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_funce (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_funcid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_jedec (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_longlink (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_longlink_mfc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_manfid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_org (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_vers_1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int parse_vers_2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

int pcmcia_parse_tuple(tuple_t *tuple, cisparse_t *parse)
{
    int ret = 0;
    
    if (tuple->TupleDataLen > tuple->TupleDataMax)
	return -EINVAL;
    switch (tuple->TupleCode) {
    case CISTPL_DEVICE:
    case CISTPL_DEVICE_A:
	ret = parse_device(tuple, &parse->device);
	break;
#ifdef CONFIG_CARDBUS
    case CISTPL_BAR:
	ret = parse_bar(tuple, &parse->bar);
	break;
    case CISTPL_CONFIG_CB:
	ret = parse_config_cb(tuple, &parse->config);
	break;
    case CISTPL_CFTABLE_ENTRY_CB:
	ret = parse_cftable_entry_cb(tuple, &parse->cftable_entry_cb);
	break;
#endif
    case CISTPL_CHECKSUM:
	ret = parse_checksum(tuple, &parse->checksum);
	break;
    case CISTPL_LONGLINK_A:
    case CISTPL_LONGLINK_C:
	ret = parse_longlink(tuple, &parse->longlink);
	break;
    case CISTPL_LONGLINK_MFC:
	ret = parse_longlink_mfc(tuple, &parse->longlink_mfc);
	break;
    case CISTPL_VERS_1:
	ret = parse_vers_1(tuple, &parse->version_1);
	break;
    case CISTPL_ALTSTR:
	ret = parse_altstr(tuple, &parse->altstr);
	break;
    case CISTPL_JEDEC_A:
    case CISTPL_JEDEC_C:
	ret = parse_jedec(tuple, &parse->jedec);
	break;
    case CISTPL_MANFID:
	ret = parse_manfid(tuple, &parse->manfid);
	break;
    case CISTPL_FUNCID:
	ret = parse_funcid(tuple, &parse->funcid);
	break;
    case CISTPL_FUNCE:
	ret = parse_funce(tuple, &parse->funce);
	break;
    case CISTPL_CONFIG:
	ret = parse_config(tuple, &parse->config);
	break;
    case CISTPL_CFTABLE_ENTRY:
	ret = parse_cftable_entry(tuple, &parse->cftable_entry);
	break;
    case CISTPL_DEVICE_GEO:
    case CISTPL_DEVICE_GEO_A:
	ret = parse_device_geo(tuple, &parse->device_geo);
	break;
    case CISTPL_VERS_2:
	ret = parse_vers_2(tuple, &parse->vers_2);
	break;
    case CISTPL_ORG:
	ret = parse_org(tuple, &parse->org);
	break;
    case CISTPL_FORMAT:
    case CISTPL_FORMAT_A:
	ret = parse_format(tuple, &parse->format);
	break;
    case CISTPL_NO_LINK:
    case CISTPL_LINKTARGET:
	ret = 0;
	break;
    default:
	ret = -EINVAL;
	break;
    }
    if (ret)
	    __cs_dbg(0, "parse_tuple failed %d\n", ret);
    return ret;
}