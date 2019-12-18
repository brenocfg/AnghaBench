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
typedef  int /*<<< orphan*/  rcc_interface_ty ;

/* Variables and functions */
 int /*<<< orphan*/  Seq_addhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interfaces ; 

__attribute__((used)) static void put(rcc_interface_ty node) {
	Seq_addhi(interfaces, node);
}