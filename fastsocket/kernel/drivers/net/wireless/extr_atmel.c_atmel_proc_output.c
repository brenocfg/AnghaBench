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
struct TYPE_4__ {int major_version; int minor_version; int build_version; } ;
struct atmel_private {int station_state; int card_type; char* firmware_id; scalar_t__ reg_domain; scalar_t__ use_wpa; scalar_t__ do_rx_crc; scalar_t__ firmware; TYPE_1__ host_info; } ;
struct TYPE_5__ {scalar_t__ reg_domain; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  CARD_TYPE_EEPROM 138 
#define  CARD_TYPE_PARALLEL_FLASH 137 
#define  CARD_TYPE_SPI_FLASH 136 
 int DRIVER_MAJOR ; 
 int DRIVER_MINOR ; 
#define  STATION_STATE_ASSOCIATING 135 
#define  STATION_STATE_AUTHENTICATING 134 
#define  STATION_STATE_DOWN 133 
#define  STATION_STATE_JOINNING 132 
#define  STATION_STATE_MGMT_ERROR 131 
#define  STATION_STATE_READY 130 
#define  STATION_STATE_REASSOCIATING 129 
#define  STATION_STATE_SCANNING 128 
 TYPE_2__* channel_table ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int atmel_proc_output (char *buf, struct atmel_private *priv)
{
	int i;
	char *p = buf;
	char *s, *r, *c;

	p += sprintf(p, "Driver version:\t\t%d.%d\n",
		     DRIVER_MAJOR, DRIVER_MINOR);

	if (priv->station_state != STATION_STATE_DOWN) {
		p += sprintf(p, "Firmware version:\t%d.%d build %d\n"
				"Firmware location:\t",
			     priv->host_info.major_version,
			     priv->host_info.minor_version,
			     priv->host_info.build_version);

		if (priv->card_type != CARD_TYPE_EEPROM)
			p += sprintf(p, "on card\n");
		else if (priv->firmware)
			p += sprintf(p, "%s loaded by host\n",
				     priv->firmware_id);
		else
			p += sprintf(p, "%s loaded by hotplug\n",
				     priv->firmware_id);

		switch (priv->card_type) {
		case CARD_TYPE_PARALLEL_FLASH:
			c = "Parallel flash";
			break;
		case CARD_TYPE_SPI_FLASH:
			c = "SPI flash\n";
			break;
		case CARD_TYPE_EEPROM:
			c = "EEPROM";
			break;
		default:
			c = "<unknown>";
		}

		r = "<unknown>";
		for (i = 0; i < ARRAY_SIZE(channel_table); i++)
			if (priv->reg_domain == channel_table[i].reg_domain)
				r = channel_table[i].name;

		p += sprintf(p, "MAC memory type:\t%s\n", c);
		p += sprintf(p, "Regulatory domain:\t%s\n", r);
		p += sprintf(p, "Host CRC checking:\t%s\n",
			     priv->do_rx_crc ? "On" : "Off");
		p += sprintf(p, "WPA-capable firmware:\t%s\n",
			     priv->use_wpa ? "Yes" : "No");
	}

	switch (priv->station_state) {
	case STATION_STATE_SCANNING:
		s = "Scanning";
		break;
	case STATION_STATE_JOINNING:
		s = "Joining";
		break;
	case STATION_STATE_AUTHENTICATING:
		s = "Authenticating";
		break;
	case STATION_STATE_ASSOCIATING:
		s = "Associating";
		break;
	case STATION_STATE_READY:
		s = "Ready";
		break;
	case STATION_STATE_REASSOCIATING:
		s = "Reassociating";
		break;
	case STATION_STATE_MGMT_ERROR:
		s = "Management error";
		break;
	case STATION_STATE_DOWN:
		s = "Down";
		break;
	default:
		s = "<unknown>";
	}

	p += sprintf(p, "Current state:\t\t%s\n", s);
	return p - buf;
}