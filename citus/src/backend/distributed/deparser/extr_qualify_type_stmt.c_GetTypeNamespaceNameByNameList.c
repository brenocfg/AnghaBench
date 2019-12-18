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
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  LookupTypeNameOid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TypeOidGetNamespaceOid (int /*<<< orphan*/ ) ; 
 char* get_namespace_name_or_temp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
GetTypeNamespaceNameByNameList(List *names)
{
	TypeName *typeName = makeTypeNameFromNameList(names);
	Oid typeOid = LookupTypeNameOid(NULL, typeName, false);
	Oid namespaceOid = TypeOidGetNamespaceOid(typeOid);
	char *nspname = get_namespace_name_or_temp(namespaceOid);
	return nspname;
}