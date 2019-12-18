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
typedef  int /*<<< orphan*/ * _cstruct ;

/* Variables and functions */
#define  ISDN_PROTO_L2_HDLC 135 
#define  ISDN_PROTO_L2_TRANS 134 
#define  ISDN_PROTO_L2_V11019 133 
#define  ISDN_PROTO_L2_V11038 132 
#define  ISDN_PROTO_L2_V11096 131 
#define  ISDN_PROTO_L2_X75BUI 130 
#define  ISDN_PROTO_L2_X75I 129 
#define  ISDN_PROTO_L2_X75UI 128 
 int /*<<< orphan*/ * b1config_async_v110 (int) ; 

__attribute__((used)) static _cstruct b1config(int l2, int l3)
{
	switch (l2) {
	case ISDN_PROTO_L2_X75I:
	case ISDN_PROTO_L2_X75UI:
	case ISDN_PROTO_L2_X75BUI:
	case ISDN_PROTO_L2_HDLC:
	case ISDN_PROTO_L2_TRANS:
	default:
		return NULL;
        case ISDN_PROTO_L2_V11096:
	    return b1config_async_v110(9600);
        case ISDN_PROTO_L2_V11019:
	    return b1config_async_v110(19200);
        case ISDN_PROTO_L2_V11038:
	    return b1config_async_v110(38400);
	}
}