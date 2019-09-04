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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  CONSOLE ;
typedef  int /*<<< orphan*/  CMD ;

/* Variables and functions */
 int DispatchNextCmdEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

bool DispatchNextCmd(CONSOLE *c, char *prompt, CMD cmd[], UINT num_cmd, void *param)
{
	return DispatchNextCmdEx(c, NULL, prompt, cmd, num_cmd, param);
}