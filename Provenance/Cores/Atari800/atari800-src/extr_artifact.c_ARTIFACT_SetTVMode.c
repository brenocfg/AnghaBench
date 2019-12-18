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
typedef  int /*<<< orphan*/  ARTIFACT_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARTIFACT_mode ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateFromTVMode (int) ; 
 int /*<<< orphan*/  UpdateMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ARTIFACT_SetTVMode(int tv_mode)
{
	ARTIFACT_t old_mode = ARTIFACT_mode;
	UpdateFromTVMode(tv_mode);
	UpdateMode(old_mode, TRUE);
}