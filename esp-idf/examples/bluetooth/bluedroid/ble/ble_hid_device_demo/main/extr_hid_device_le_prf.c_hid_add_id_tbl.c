#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* mode; scalar_t__ cccdHandle; scalar_t__ handle; void* type; void* id; } ;
struct TYPE_5__ {scalar_t__* att_tbl; } ;
struct TYPE_6__ {TYPE_1__ hidd_inst; } ;

/* Variables and functions */
 size_t HIDD_LE_IDX_BOOT_KB_IN_REPORT_VAL ; 
 size_t HIDD_LE_IDX_BOOT_KB_OUT_REPORT_VAL ; 
 size_t HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_VAL ; 
 size_t HIDD_LE_IDX_REPORT_CC_IN_CCC ; 
 size_t HIDD_LE_IDX_REPORT_CC_IN_VAL ; 
 size_t HIDD_LE_IDX_REPORT_KEY_IN_CCC ; 
 size_t HIDD_LE_IDX_REPORT_KEY_IN_VAL ; 
 size_t HIDD_LE_IDX_REPORT_LED_OUT_VAL ; 
 size_t HIDD_LE_IDX_REPORT_MOUSE_IN_VAL ; 
 size_t HIDD_LE_IDX_REPORT_VAL ; 
 int /*<<< orphan*/  HID_NUM_REPORTS ; 
 void* HID_PROTOCOL_MODE_BOOT ; 
 void* HID_PROTOCOL_MODE_REPORT ; 
 void** hidReportRefCCIn ; 
 void** hidReportRefFeature ; 
 void** hidReportRefKeyIn ; 
 void** hidReportRefLedOut ; 
 void** hidReportRefMouseIn ; 
 int /*<<< orphan*/  hid_dev_register_reports (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* hid_rpt_map ; 
 TYPE_2__ hidd_le_env ; 

__attribute__((used)) static void hid_add_id_tbl(void)
{
     // Mouse input report
      hid_rpt_map[0].id = hidReportRefMouseIn[0];
      hid_rpt_map[0].type = hidReportRefMouseIn[1];
      hid_rpt_map[0].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_MOUSE_IN_VAL];
      hid_rpt_map[0].cccdHandle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_MOUSE_IN_VAL];
      hid_rpt_map[0].mode = HID_PROTOCOL_MODE_REPORT;

      // Key input report
      hid_rpt_map[1].id = hidReportRefKeyIn[0];
      hid_rpt_map[1].type = hidReportRefKeyIn[1];
      hid_rpt_map[1].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_KEY_IN_VAL];
      hid_rpt_map[1].cccdHandle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_KEY_IN_CCC];
      hid_rpt_map[1].mode = HID_PROTOCOL_MODE_REPORT;

      // Consumer Control input report
      hid_rpt_map[2].id = hidReportRefCCIn[0];
      hid_rpt_map[2].type = hidReportRefCCIn[1];
      hid_rpt_map[2].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_CC_IN_VAL];
      hid_rpt_map[2].cccdHandle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_CC_IN_CCC];
      hid_rpt_map[2].mode = HID_PROTOCOL_MODE_REPORT;

      // LED output report
      hid_rpt_map[3].id = hidReportRefLedOut[0];
      hid_rpt_map[3].type = hidReportRefLedOut[1];
      hid_rpt_map[3].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_LED_OUT_VAL];
      hid_rpt_map[3].cccdHandle = 0;
      hid_rpt_map[3].mode = HID_PROTOCOL_MODE_REPORT;

      // Boot keyboard input report
      // Use same ID and type as key input report
      hid_rpt_map[4].id = hidReportRefKeyIn[0];
      hid_rpt_map[4].type = hidReportRefKeyIn[1];
      hid_rpt_map[4].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_BOOT_KB_IN_REPORT_VAL];
      hid_rpt_map[4].cccdHandle = 0;
      hid_rpt_map[4].mode = HID_PROTOCOL_MODE_BOOT;

      // Boot keyboard output report
      // Use same ID and type as LED output report
      hid_rpt_map[5].id = hidReportRefLedOut[0];
      hid_rpt_map[5].type = hidReportRefLedOut[1];
      hid_rpt_map[5].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_BOOT_KB_OUT_REPORT_VAL];
      hid_rpt_map[5].cccdHandle = 0;
      hid_rpt_map[5].mode = HID_PROTOCOL_MODE_BOOT;

      // Boot mouse input report
      // Use same ID and type as mouse input report
      hid_rpt_map[6].id = hidReportRefMouseIn[0];
      hid_rpt_map[6].type = hidReportRefMouseIn[1];
      hid_rpt_map[6].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_VAL];
      hid_rpt_map[6].cccdHandle = 0;
      hid_rpt_map[6].mode = HID_PROTOCOL_MODE_BOOT;

      // Feature report
      hid_rpt_map[7].id = hidReportRefFeature[0];
      hid_rpt_map[7].type = hidReportRefFeature[1];
      hid_rpt_map[7].handle = hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_REPORT_VAL];
      hid_rpt_map[7].cccdHandle = 0;
      hid_rpt_map[7].mode = HID_PROTOCOL_MODE_REPORT;


  // Setup report ID map
  hid_dev_register_reports(HID_NUM_REPORTS, hid_rpt_map);
}