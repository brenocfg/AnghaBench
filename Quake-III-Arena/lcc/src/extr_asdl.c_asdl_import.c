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
typedef  int /*<<< orphan*/  Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  dopending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Import (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symboluid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asdl_import(Symbol p) {
	dopending(p);
	put(rcc_Import(symboluid(p)));
}