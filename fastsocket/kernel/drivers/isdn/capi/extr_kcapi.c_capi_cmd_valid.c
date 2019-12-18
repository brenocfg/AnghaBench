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
typedef  int u8 ;

/* Variables and functions */
#define  CAPI_ALERT 142 
#define  CAPI_CONNECT 141 
#define  CAPI_CONNECT_ACTIVE 140 
#define  CAPI_CONNECT_B3 139 
#define  CAPI_CONNECT_B3_ACTIVE 138 
#define  CAPI_CONNECT_B3_T90_ACTIVE 137 
#define  CAPI_DATA_B3 136 
#define  CAPI_DISCONNECT 135 
#define  CAPI_DISCONNECT_B3 134 
#define  CAPI_FACILITY 133 
#define  CAPI_INFO 132 
#define  CAPI_LISTEN 131 
#define  CAPI_MANUFACTURER 130 
#define  CAPI_RESET_B3 129 
#define  CAPI_SELECT_B_PROTOCOL 128 

__attribute__((used)) static inline int capi_cmd_valid(u8 cmd)
{
	switch (cmd) {
	case CAPI_ALERT:
	case CAPI_CONNECT:
	case CAPI_CONNECT_ACTIVE:
	case CAPI_CONNECT_B3_ACTIVE:
	case CAPI_CONNECT_B3:
	case CAPI_CONNECT_B3_T90_ACTIVE:
	case CAPI_DATA_B3:
	case CAPI_DISCONNECT_B3:
	case CAPI_DISCONNECT:
	case CAPI_FACILITY:
	case CAPI_INFO:
	case CAPI_LISTEN:
	case CAPI_MANUFACTURER:
	case CAPI_RESET_B3:
	case CAPI_SELECT_B_PROTOCOL:
		return 1;
	}
	return 0;
}