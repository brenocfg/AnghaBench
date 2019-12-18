#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tDIS_STATUS ;
typedef  int tDIS_ATTR_BIT ;
struct TYPE_11__ {int len; int /*<<< orphan*/  p_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  product_version; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id_src; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_12__ {TYPE_4__ data_str; TYPE_2__ pnp_id; int /*<<< orphan*/  system_id; } ;
typedef  TYPE_5__ tDIS_ATTR ;
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_8__ {int /*<<< orphan*/  product_version; int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id_src; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_10__ {int** data_string; TYPE_1__ pnp_id; int /*<<< orphan*/  system_id; } ;
struct TYPE_13__ {TYPE_3__ dis_value; } ;

/* Variables and functions */
 int DIS_ATTR_PNP_ID_BIT ; 
 int DIS_ATTR_SYS_ID_BIT ; 
 int /*<<< orphan*/  DIS_ILLEGAL_PARAM ; 
 int DIS_MAX_CHAR_NUM ; 
 int /*<<< orphan*/  DIS_NO_RESOURCES ; 
 int /*<<< orphan*/  DIS_SUCCESS ; 
 TYPE_6__ dis_cb ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osi_free (int*) ; 
 scalar_t__ osi_malloc (int) ; 

tDIS_STATUS DIS_SrUpdate(tDIS_ATTR_BIT dis_attr_bit, tDIS_ATTR *p_info)
{
    UINT8           i = 1;
    tDIS_STATUS     st = DIS_SUCCESS;

    if (dis_attr_bit & DIS_ATTR_SYS_ID_BIT) {
        dis_cb.dis_value.system_id = p_info->system_id;
    } else if (dis_attr_bit & DIS_ATTR_PNP_ID_BIT) {
        dis_cb.dis_value.pnp_id.vendor_id         = p_info->pnp_id.vendor_id;
        dis_cb.dis_value.pnp_id.vendor_id_src     = p_info->pnp_id.vendor_id_src;
        dis_cb.dis_value.pnp_id.product_id        = p_info->pnp_id.product_id;
        dis_cb.dis_value.pnp_id.product_version   = p_info->pnp_id.product_version;
    } else {
        st = DIS_ILLEGAL_PARAM;

        while (dis_attr_bit && i < (DIS_MAX_CHAR_NUM - 1 )) {
            if (dis_attr_bit & (UINT16)(1 << i)) {
                if (dis_cb.dis_value.data_string[i - 1] != NULL) {
                    osi_free(dis_cb.dis_value.data_string[i - 1]);
                }
                /* coverity[OVERRUN-STATIC] False-positive : when i = 8, (1 << i) == DIS_ATTR_PNP_ID_BIT, and it will never come down here
                CID 49902: Out-of-bounds read (OVERRUN_STATIC)
                Overrunning static array "dis_cb.dis_value.data_string", with 7 elements, at position 7 with index variable "i".
                */
                if ((dis_cb.dis_value.data_string[i - 1] = (UINT8 *)osi_malloc((UINT16)(p_info->data_str.len + 1))) != NULL) {

                    memcpy(dis_cb.dis_value.data_string[i - 1], p_info->data_str.p_data, p_info->data_str.len);
                    dis_cb.dis_value.data_string[i - 1][p_info->data_str.len] = 0; /* make sure null terminate */
                    st = DIS_SUCCESS;
                } else {
                    st = DIS_NO_RESOURCES;
                }

                break;
            }
            i ++;
        }
    }
    return st;
}