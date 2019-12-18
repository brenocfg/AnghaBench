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
#define  C2_QP_STATE_CLOSING 133 
#define  C2_QP_STATE_CONNECTING 132 
#define  C2_QP_STATE_ERROR 131 
#define  C2_QP_STATE_IDLE 130 
#define  C2_QP_STATE_RTS 129 
#define  C2_QP_STATE_TERMINATE 128 

__attribute__((used)) static const char *to_qp_state_str(int state)
{
	switch (state) {
	case C2_QP_STATE_IDLE:
		return "C2_QP_STATE_IDLE";
	case C2_QP_STATE_CONNECTING:
		return "C2_QP_STATE_CONNECTING";
	case C2_QP_STATE_RTS:
		return "C2_QP_STATE_RTS";
	case C2_QP_STATE_CLOSING:
		return "C2_QP_STATE_CLOSING";
	case C2_QP_STATE_TERMINATE:
		return "C2_QP_STATE_TERMINATE";
	case C2_QP_STATE_ERROR:
		return "C2_QP_STATE_ERROR";
	default:
		return "<invalid QP state>";
	};
}