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
typedef  int /*<<< orphan*/  IniContext ;

/* Variables and functions */
 int fdfs_get_ini_context_from_tracker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int fdfs_get_storage_ids_from_tracker_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_tracker_group ; 
 int /*<<< orphan*/  iniFreeContext (int /*<<< orphan*/ *) ; 
 int iniGetBoolValue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fdfs_get_params_from_tracker(bool *use_storage_id)
{
    IniContext iniContext;
	int result;
	bool continue_flag;

	continue_flag = false;
	if ((result=fdfs_get_ini_context_from_tracker(&g_tracker_group,
		&iniContext, &continue_flag, false, NULL)) != 0)
    {
        return result;
    }

	*use_storage_id = iniGetBoolValue(NULL, "use_storage_id",
            &iniContext, false);
    iniFreeContext(&iniContext);

	if (*use_storage_id)
	{
		result = fdfs_get_storage_ids_from_tracker_group(
				&g_tracker_group);
	}

    return result;
}