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
 int /*<<< orphan*/  FDFS_ID_TYPE_IP_ADDRESS ; 
 int /*<<< orphan*/  FDFS_ID_TYPE_SERVER_ID ; 
 int fdfs_load_storage_ids_from_file (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_id_type_in_filename ; 
 int /*<<< orphan*/  g_use_storage_id ; 
 int /*<<< orphan*/  iniGetBoolValue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 char* iniGetStrValue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int tracker_load_storage_id_info(const char *config_filename, \
		IniContext *pItemContext)
{
	char *pIdType;

	g_use_storage_id = iniGetBoolValue(NULL, "use_storage_id", \
				pItemContext, false);
	if (!g_use_storage_id)
	{
		return 0;
	}

	pIdType = iniGetStrValue(NULL, "id_type_in_filename", \
			pItemContext);
	if (pIdType != NULL && strcasecmp(pIdType, "id") == 0)
	{
		g_id_type_in_filename = FDFS_ID_TYPE_SERVER_ID;
	}
	else
	{
		g_id_type_in_filename = FDFS_ID_TYPE_IP_ADDRESS;
	}

	return fdfs_load_storage_ids_from_file(config_filename, pItemContext);
}