#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ classId; int /*<<< orphan*/  objectId; } ;
typedef  TYPE_1__ ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  CITUS_NAME ; 
 scalar_t__ ExtensionRelationId ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* get_extension_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
CitusExtensionObject(const ObjectAddress *objectAddress)
{
	char *extensionName = false;

	if (objectAddress->classId != ExtensionRelationId)
	{
		return false;
	}

	extensionName = get_extension_name(objectAddress->objectId);
	if (extensionName != NULL &&
		strncasecmp(extensionName, CITUS_NAME, NAMEDATALEN) == 0)
	{
		return true;
	}

	return false;
}