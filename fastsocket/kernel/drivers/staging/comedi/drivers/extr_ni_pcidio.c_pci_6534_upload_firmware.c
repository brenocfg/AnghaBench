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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 size_t COMEDI_DEVCONF_AUX_DATA0_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA1_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA2_LENGTH ; 
 size_t COMEDI_DEVCONF_AUX_DATA_LENGTH ; 
 void* comedi_aux_data (int*,int) ; 
 int /*<<< orphan*/  pci_6534_init_main_fpga (struct comedi_device*) ; 
 int pci_6534_load_fpga (struct comedi_device*,int,void*,int) ; 
 int pci_6534_reset_fpgas (struct comedi_device*) ; 

__attribute__((used)) static int pci_6534_upload_firmware(struct comedi_device *dev, int options[])
{
	int ret;
	void *main_fpga_data, *scarab_a_data, *scarab_b_data;
	int main_fpga_data_len, scarab_a_data_len, scarab_b_data_len;

	if (options[COMEDI_DEVCONF_AUX_DATA_LENGTH] == 0)
		return 0;
	ret = pci_6534_reset_fpgas(dev);
	if (ret < 0)
		return ret;
	main_fpga_data = comedi_aux_data(options, 0);
	main_fpga_data_len = options[COMEDI_DEVCONF_AUX_DATA0_LENGTH];
	ret = pci_6534_load_fpga(dev, 2, main_fpga_data, main_fpga_data_len);
	if (ret < 0)
		return ret;
	pci_6534_init_main_fpga(dev);
	scarab_a_data = comedi_aux_data(options, 1);
	scarab_a_data_len = options[COMEDI_DEVCONF_AUX_DATA1_LENGTH];
	ret = pci_6534_load_fpga(dev, 0, scarab_a_data, scarab_a_data_len);
	if (ret < 0)
		return ret;
	scarab_b_data = comedi_aux_data(options, 2);
	scarab_b_data_len = options[COMEDI_DEVCONF_AUX_DATA2_LENGTH];
	ret = pci_6534_load_fpga(dev, 1, scarab_b_data, scarab_b_data_len);
	if (ret < 0)
		return ret;
	return 0;
}