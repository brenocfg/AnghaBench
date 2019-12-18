#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int offset; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_FCR_INIT_CRC ; 
 int /*<<< orphan*/  l2c_fcr_updcrc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT16 l2c_fcr_tx_get_fcs (BT_HDR *p_buf)
{
    UINT8   *p = ((UINT8 *) (p_buf + 1)) + p_buf->offset;

    return (l2c_fcr_updcrc (L2CAP_FCR_INIT_CRC, p, p_buf->len));
}