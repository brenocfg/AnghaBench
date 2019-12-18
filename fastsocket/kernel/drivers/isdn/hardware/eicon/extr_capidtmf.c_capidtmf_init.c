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
struct TYPE_4__ {int /*<<< orphan*/  ulaw; } ;
typedef  TYPE_1__ t_capidtmf_state ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  capidtmf_recv_init (TYPE_1__*) ; 

void capidtmf_init (t_capidtmf_state   *p_state, byte ulaw)
{
  p_state->ulaw = ulaw;
  capidtmf_recv_init (p_state);
}