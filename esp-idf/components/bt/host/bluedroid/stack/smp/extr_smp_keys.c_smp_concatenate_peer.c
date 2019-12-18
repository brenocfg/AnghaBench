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
struct TYPE_3__ {int /*<<< orphan*/  peer_r_key; int /*<<< orphan*/  peer_i_key; int /*<<< orphan*/  peer_enc_size; int /*<<< orphan*/  peer_auth_req; int /*<<< orphan*/  peer_oob_flag; int /*<<< orphan*/  peer_io_caps; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void smp_concatenate_peer( tSMP_CB *p_cb, UINT8 **p_data, UINT8 op_code)
{
    UINT8   *p = *p_data;

    SMP_TRACE_DEBUG ("smp_concatenate_peer \n");
    UINT8_TO_STREAM(p, op_code);
    UINT8_TO_STREAM(p, p_cb->peer_io_caps);
    UINT8_TO_STREAM(p, p_cb->peer_oob_flag);
    UINT8_TO_STREAM(p, p_cb->peer_auth_req);
    UINT8_TO_STREAM(p, p_cb->peer_enc_size);
    UINT8_TO_STREAM(p, p_cb->peer_i_key);
    UINT8_TO_STREAM(p, p_cb->peer_r_key);

    *p_data = p;
}