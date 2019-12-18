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
struct TYPE_3__ {void* p_data; int /*<<< orphan*/  key_type; } ;
typedef  TYPE_1__ tSMP_KEY ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  void* BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_KEY_READY_EVT ; 
 int /*<<< orphan*/  SMP_KEY_TYPE_TK ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  UINT32_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_cb ; 
 int /*<<< orphan*/  smp_sm_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void smp_convert_string_to_tk(BT_OCTET16 tk, UINT32 passkey)
{
    UINT8   *p = tk;
    tSMP_KEY    key;
    SMP_TRACE_EVENT("smp_convert_string_to_tk\n");
    UINT32_TO_STREAM(p, passkey);

    key.key_type    = SMP_KEY_TYPE_TK;
    key.p_data      = tk;

    smp_sm_event(&smp_cb, SMP_KEY_READY_EVT, &key);
}