#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* ch_flow_control; int last_flow_control_ch; scalar_t__* ch_flow_plci; } ;
struct TYPE_7__ {scalar_t__ Id; TYPE_1__* adapter; } ;
struct TYPE_6__ {int manufacturer_features; } ;
typedef  TYPE_2__ PLCI ;
typedef  TYPE_3__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL ; 
 int N_XON_REQ ; 

__attribute__((used)) static int find_channel_with_pending_x_on (DIVA_CAPI_ADAPTER   * a, PLCI   * plci) {
  int max_ch = ARRAY_SIZE(a->ch_flow_control);
  int i;

  if (!(plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL)) {
    return (0);
  }

  if (a->last_flow_control_ch >= max_ch) {
    a->last_flow_control_ch = 1;
  }
  for (i=a->last_flow_control_ch; i < max_ch; i++) {
    if ((a->ch_flow_control[i] & N_XON_REQ) &&
        (plci->Id == a->ch_flow_plci[i])) {
      a->last_flow_control_ch = i+1;
      return (i);
    }
  }

  for (i = 1; i < a->last_flow_control_ch; i++) {
    if ((a->ch_flow_control[i] & N_XON_REQ) &&
        (plci->Id == a->ch_flow_plci[i])) {
      a->last_flow_control_ch = i+1;
      return (i);
    }
  }

  return (0);
}