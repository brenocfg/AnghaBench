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
 int AUX_RGB ; 
 int AUX_SINGLE ; 
 int /*<<< orphan*/  WIN_SIZE ; 
 int /*<<< orphan*/  auxInitDisplayMode (int) ; 
 int /*<<< orphan*/  auxInitPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auxInitWindow (char*) ; 

void InitWindow (void)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, WIN_SIZE, WIN_SIZE);
    auxInitWindow ("qcsg");
}