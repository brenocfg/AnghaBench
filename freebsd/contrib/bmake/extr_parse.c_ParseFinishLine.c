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

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseHasCommands ; 
 int /*<<< orphan*/  Suff_EndTransform ; 
 scalar_t__ inLine ; 
 int /*<<< orphan*/ * targets ; 

__attribute__((used)) static void
ParseFinishLine(void)
{
    if (inLine) {
	Lst_ForEach(targets, Suff_EndTransform, NULL);
	Lst_Destroy(targets, ParseHasCommands);
	targets = NULL;
	inLine = FALSE;
    }
}