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
typedef  int uint8_t ;

/* Variables and functions */
#define  FLOW_DIVERT_PKT_APP_MAP_CREATE 134 
#define  FLOW_DIVERT_PKT_CLOSE 133 
#define  FLOW_DIVERT_PKT_CONNECT 132 
#define  FLOW_DIVERT_PKT_CONNECT_RESULT 131 
#define  FLOW_DIVERT_PKT_DATA 130 
#define  FLOW_DIVERT_PKT_PROPERTIES_UPDATE 129 
#define  FLOW_DIVERT_PKT_READ_NOTIFY 128 

__attribute__((used)) static const char *
flow_divert_packet_type2str(uint8_t packet_type)
{
	switch (packet_type) {
		case FLOW_DIVERT_PKT_CONNECT:
			return "connect";
		case FLOW_DIVERT_PKT_CONNECT_RESULT:
			return "connect result";
		case FLOW_DIVERT_PKT_DATA:
			return "data";
		case FLOW_DIVERT_PKT_CLOSE:
			return "close";
		case FLOW_DIVERT_PKT_READ_NOTIFY:
			return "read notification";
		case FLOW_DIVERT_PKT_PROPERTIES_UPDATE:
			return "properties update";
		case FLOW_DIVERT_PKT_APP_MAP_CREATE:
			return "app map create";
		default:
			return "unknown";
	}
}