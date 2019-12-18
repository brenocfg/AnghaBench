#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_data_write (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

UINT8 L2CA_DataWriteEx (UINT16 cid, BT_HDR *p_data, UINT16 flags)
{
    L2CAP_TRACE_API ("L2CA_DataWriteEx()  CID: 0x%04x  Len: %d Flags:0x%04X",
                     cid, p_data->len, flags);
    return l2c_data_write (cid, p_data, flags);
}