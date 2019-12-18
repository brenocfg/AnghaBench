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
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CFG_RW ;

/* Variables and functions */
 int /*<<< orphan*/ * NewCfgRwEx (int /*<<< orphan*/ **,char*,int) ; 

CFG_RW *NewCfgRw(FOLDER **root, char *cfg_name)
{
	return NewCfgRwEx(root, cfg_name, false);
}