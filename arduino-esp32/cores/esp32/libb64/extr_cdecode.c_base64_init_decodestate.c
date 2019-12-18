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
struct TYPE_3__ {scalar_t__ plainchar; int /*<<< orphan*/  step; } ;
typedef  TYPE_1__ base64_decodestate ;

/* Variables and functions */
 int /*<<< orphan*/  step_a ; 

void base64_init_decodestate(base64_decodestate* state_in){
  state_in->step = step_a;
  state_in->plainchar = 0;
}