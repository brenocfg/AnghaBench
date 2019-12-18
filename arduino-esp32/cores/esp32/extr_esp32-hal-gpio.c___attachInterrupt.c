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
typedef  int /*<<< orphan*/  voidFuncPtrArg ;
typedef  scalar_t__ voidFuncPtr ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  __attachInterruptFunctionalArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

extern void __attachInterrupt(uint8_t pin, voidFuncPtr userFunc, int intr_type) {
    __attachInterruptFunctionalArg(pin, (voidFuncPtrArg)userFunc, NULL, intr_type, false);
}