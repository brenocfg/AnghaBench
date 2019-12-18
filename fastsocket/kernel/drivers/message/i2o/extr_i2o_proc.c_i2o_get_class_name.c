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

/* Variables and functions */
#define  I2O_CLASS_ATE_PERIPHERAL 143 
#define  I2O_CLASS_ATE_PORT 142 
#define  I2O_CLASS_BUS_ADAPTER 141 
#define  I2O_CLASS_DDM 140 
#define  I2O_CLASS_EXECUTIVE 139 
#define  I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL 138 
#define  I2O_CLASS_FIBRE_CHANNEL_PORT 137 
#define  I2O_CLASS_FLOPPY_CONTROLLER 136 
#define  I2O_CLASS_FLOPPY_DEVICE 135 
#define  I2O_CLASS_LAN 134 
#define  I2O_CLASS_PEER_TRANSPORT 133 
#define  I2O_CLASS_PEER_TRANSPORT_AGENT 132 
#define  I2O_CLASS_RANDOM_BLOCK_STORAGE 131 
#define  I2O_CLASS_SCSI_PERIPHERAL 130 
#define  I2O_CLASS_SEQUENTIAL_STORAGE 129 
#define  I2O_CLASS_WAN 128 

__attribute__((used)) static const char *i2o_get_class_name(int class)
{
	int idx = 16;
	static char *i2o_class_name[] = {
		"Executive",
		"Device Driver Module",
		"Block Device",
		"Tape Device",
		"LAN Interface",
		"WAN Interface",
		"Fibre Channel Port",
		"Fibre Channel Device",
		"SCSI Device",
		"ATE Port",
		"ATE Device",
		"Floppy Controller",
		"Floppy Device",
		"Secondary Bus Port",
		"Peer Transport Agent",
		"Peer Transport",
		"Unknown"
	};

	switch (class & 0xfff) {
	case I2O_CLASS_EXECUTIVE:
		idx = 0;
		break;
	case I2O_CLASS_DDM:
		idx = 1;
		break;
	case I2O_CLASS_RANDOM_BLOCK_STORAGE:
		idx = 2;
		break;
	case I2O_CLASS_SEQUENTIAL_STORAGE:
		idx = 3;
		break;
	case I2O_CLASS_LAN:
		idx = 4;
		break;
	case I2O_CLASS_WAN:
		idx = 5;
		break;
	case I2O_CLASS_FIBRE_CHANNEL_PORT:
		idx = 6;
		break;
	case I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL:
		idx = 7;
		break;
	case I2O_CLASS_SCSI_PERIPHERAL:
		idx = 8;
		break;
	case I2O_CLASS_ATE_PORT:
		idx = 9;
		break;
	case I2O_CLASS_ATE_PERIPHERAL:
		idx = 10;
		break;
	case I2O_CLASS_FLOPPY_CONTROLLER:
		idx = 11;
		break;
	case I2O_CLASS_FLOPPY_DEVICE:
		idx = 12;
		break;
	case I2O_CLASS_BUS_ADAPTER:
		idx = 13;
		break;
	case I2O_CLASS_PEER_TRANSPORT_AGENT:
		idx = 14;
		break;
	case I2O_CLASS_PEER_TRANSPORT:
		idx = 15;
		break;
	}

	return i2o_class_name[idx];
}