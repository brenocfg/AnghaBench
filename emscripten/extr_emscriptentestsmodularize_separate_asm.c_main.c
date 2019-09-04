#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  inputData; int /*<<< orphan*/  weHaveExecutedSomeCCode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM_ASM (int /*<<< orphan*/ ) ; 
 TYPE_1__ Module ; 

int main()
{
	// Copy a field around to mark to JavaScript code that we have successfully completed the main() of this program.
	EM_ASM(Module.weHaveExecutedSomeCCode = Module.inputData);
}