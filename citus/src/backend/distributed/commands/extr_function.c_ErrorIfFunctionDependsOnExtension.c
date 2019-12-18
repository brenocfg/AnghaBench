#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ const ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsObjectAddressOwnedByExtension (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* getObjectIdentity (TYPE_1__ const*) ; 

__attribute__((used)) static void
ErrorIfFunctionDependsOnExtension(const ObjectAddress *functionAddress)
{
	/* captures the extension address during lookup */
	ObjectAddress extensionAddress = { 0 };

	if (IsObjectAddressOwnedByExtension(functionAddress, &extensionAddress))
	{
		char *functionName = getObjectIdentity(functionAddress);
		char *extensionName = getObjectIdentity(&extensionAddress);
		ereport(ERROR, (errmsg("unable to create a distributed function from functions "
							   "owned by an extension"),
						errdetail("Function \"%s\" has a dependency on extension \"%s\". "
								  "Functions depending on an extension cannot be "
								  "distributed. Create the function by creating the "
								  "extension on the workers.", functionName,
								  extensionName)));
	}
}