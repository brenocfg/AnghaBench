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
struct IsdnCardState {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCOFI_TIMEOUT ; 
 int /*<<< orphan*/  arcofi_fsm (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arcofi_timer(struct IsdnCardState *cs) {
	arcofi_fsm(cs, ARCOFI_TIMEOUT, NULL);
}