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
struct dvb_usb_adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CINERGYT2_EP1_CONTROL_STREAM_TRANSFER ; 
 int dvb_usb_generic_rw (int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cinergyt2_streaming_ctrl(struct dvb_usb_adapter *adap, int enable)
{
	char buf[] = { CINERGYT2_EP1_CONTROL_STREAM_TRANSFER, enable ? 1 : 0 };
	char result[64];
	return dvb_usb_generic_rw(adap->dev, buf, sizeof(buf), result,
				sizeof(result), 0);
}