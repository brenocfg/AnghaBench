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
typedef  int u8_t ;
struct hci_pcb {int dummy; } ;
struct bt_state {int dummy; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_CONN ; 
 scalar_t__ ERR_OK ; 
#define  HCI_HC_BB_OGF 129 
 int HCI_HOST_BUF_SIZE ; 
#define  HCI_INFO_PARAM 128 
 int HCI_READ_BD_ADDR ; 
 int HCI_READ_BUFFER_SIZE ; 
 int HCI_READ_LOCAL_FEATURES ; 
 int HCI_READ_LOCAL_VERSION ; 
 int HCI_RESET ; 
 int HCI_SUCCESS ; 
 int HCI_WRITE_COD ; 
 int HCI_WRITE_LOCAL_NAME ; 
 int HCI_WRITE_PIN_TYPE ; 
 int /*<<< orphan*/  LOG (char*,int,int) ; 
 int /*<<< orphan*/  __bte_cmdfinish (struct bt_state*,scalar_t__) ; 
 int /*<<< orphan*/  bte_hci_initcore_complete2 ; 
 int /*<<< orphan*/  hci_cmd_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_host_buffer_size () ; 
 int /*<<< orphan*/  hci_read_bd_addr () ; 
 int /*<<< orphan*/  hci_read_buffer_size () ; 
 int /*<<< orphan*/  hci_read_local_features () ; 
 int /*<<< orphan*/  hci_read_local_version () ; 
 int /*<<< orphan*/  hci_write_cod (int*) ; 
 int /*<<< orphan*/  hci_write_inquiry_mode (int) ; 
 int /*<<< orphan*/  hci_write_local_name (int*,int) ; 
 int /*<<< orphan*/  hci_write_pin_type (int) ; 

err_t bte_hci_initcore_complete(void *arg,struct hci_pcb *pcb,u8_t ogf,u8_t ocf,u8_t result)
{
	err_t err = ERR_OK;
	u8_t dev_cod[] = {0x00, 0x1f,0x00};
	struct bt_state *state = (struct bt_state*)arg;

	LOG("bte_hci_initcore_complete(%02x,%02x)\n",ogf,ocf);
	switch(ogf) {
		case HCI_INFO_PARAM:
			if(ocf==HCI_READ_BUFFER_SIZE) {
				if(result==HCI_SUCCESS) {
					hci_write_cod(dev_cod);
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_READ_LOCAL_VERSION) {
				if(result==HCI_SUCCESS) {
					hci_read_bd_addr();
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_READ_BD_ADDR) {
				if(result==HCI_SUCCESS) {
					hci_read_local_features();
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_READ_LOCAL_FEATURES) {
				if(result==HCI_SUCCESS) {
					hci_cmd_complete(bte_hci_initcore_complete2);
					hci_write_inquiry_mode(0x01);
				} else
					err = ERR_CONN;
			}
			break;
		case HCI_HC_BB_OGF:
			if(ocf==HCI_RESET) {
				if(result==HCI_SUCCESS) {
					hci_read_buffer_size();
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_WRITE_COD) {
				if(result==HCI_SUCCESS) {
					hci_write_local_name((u8_t*)"",1);
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_WRITE_LOCAL_NAME) {
				if(result==HCI_SUCCESS) {
					hci_write_pin_type(0x00);
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_WRITE_PIN_TYPE) {
				if(result==HCI_SUCCESS) {
					hci_host_buffer_size();
				} else
					err = ERR_CONN;
			} else if(ocf==HCI_HOST_BUF_SIZE) {
				if(result==HCI_SUCCESS) {
					hci_read_local_version();
				} else
					err = ERR_CONN;
			}
			break;
		default:
			LOG("Unknown command complete event. OGF = 0x%x OCF = 0x%x\n", ogf, ocf);
			err = ERR_CONN;
			break;
	}

	if(err!=ERR_OK) __bte_cmdfinish(state,err);
	return err;
}