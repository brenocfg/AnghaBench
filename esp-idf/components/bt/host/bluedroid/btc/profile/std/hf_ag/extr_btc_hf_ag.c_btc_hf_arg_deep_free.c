#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int act; scalar_t__ arg; } ;
typedef  TYPE_6__ btc_msg_t ;
struct TYPE_12__ {int /*<<< orphan*/  number; } ;
struct TYPE_11__ {int /*<<< orphan*/  number; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  unat; } ;
struct TYPE_15__ {TYPE_4__ phone; TYPE_3__ cnum_rep; TYPE_2__ clcc_rep; TYPE_1__ cops_rep; TYPE_5__ unat_rep; } ;
typedef  TYPE_7__ btc_hf_args_t ;

/* Variables and functions */
#define  BTC_HF_AC_INCALL_EVT 135 
#define  BTC_HF_CLCC_RESPONSE_EVT 134 
#define  BTC_HF_CNUM_RESPONSE_EVT 133 
#define  BTC_HF_COPS_RESPONSE_EVT 132 
#define  BTC_HF_END_CALL_EVT 131 
#define  BTC_HF_OUT_CALL_EVT 130 
#define  BTC_HF_RJ_INCALL_EVT 129 
#define  BTC_HF_UNAT_RESPONSE_EVT 128 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void btc_hf_arg_deep_free(btc_msg_t *msg)
{
    btc_hf_args_t *arg = (btc_hf_args_t *)msg->arg;

    switch (msg->act) {
        case BTC_HF_UNAT_RESPONSE_EVT:
        {
            if (arg->unat_rep.unat) {
                osi_free(arg->unat_rep.unat);
            }
            break;
        }

        case BTC_HF_COPS_RESPONSE_EVT:
        {
            if (arg->cops_rep.name) {
                osi_free(arg->cops_rep.name);
            }
            break;
        }

        case BTC_HF_CLCC_RESPONSE_EVT:
        {
            if (arg->clcc_rep.number) {
                osi_free(arg->clcc_rep.number);
            }
            break;
        }

        case BTC_HF_CNUM_RESPONSE_EVT:
        {
            if (arg->cnum_rep.number) {
                osi_free(arg->cnum_rep.number);
            }
            break;
        }
        
        case BTC_HF_AC_INCALL_EVT:
        case BTC_HF_RJ_INCALL_EVT:
        case BTC_HF_OUT_CALL_EVT:
        case BTC_HF_END_CALL_EVT:
        {
            if (arg->phone.number) {
                osi_free(arg->phone.number);
            }
            break;
        }

        default:
            break;
    }
}