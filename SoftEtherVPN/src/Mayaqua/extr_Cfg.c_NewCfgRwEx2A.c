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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CFG_RW ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewCfgRwEx2W (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

CFG_RW *NewCfgRwEx2A(FOLDER **root, char *cfg_name_a, bool dont_backup, char *template_name_a)
{
	CFG_RW *ret;
	wchar_t *cfg_name_w = CopyStrToUni(cfg_name_a);
	wchar_t *template_name_w = CopyStrToUni(template_name_a);

	ret = NewCfgRwEx2W(root, cfg_name_w, dont_backup, template_name_w);

	Free(cfg_name_w);
	Free(template_name_w);

	return ret;
}