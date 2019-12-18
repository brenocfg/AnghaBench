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
typedef  int /*<<< orphan*/  spvc_resources ;
typedef  int /*<<< orphan*/  spvc_resource_type ;
struct TYPE_3__ {int id; int base_type_id; int type_id; char* name; } ;
typedef  TYPE_1__ spvc_reflected_resource ;
typedef  int /*<<< orphan*/  spvc_compiler ;

/* Variables and functions */
 int /*<<< orphan*/  SPVC_CHECKED_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpvDecorationBinding ; 
 int /*<<< orphan*/  SpvDecorationDescriptorSet ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int spvc_compiler_get_decoration (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spvc_resources_get_resource_list_for_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const**,size_t*) ; 

__attribute__((used)) static void dump_resource_list(spvc_compiler compiler, spvc_resources resources, spvc_resource_type type, const char *tag)
{
	const spvc_reflected_resource *list = NULL;
	size_t count = 0;
	size_t i;
	SPVC_CHECKED_CALL(spvc_resources_get_resource_list_for_type(resources, type, &list, &count));
	printf("%s\n", tag);
	for (i = 0; i < count; i++)
	{
		printf("ID: %u, BaseTypeID: %u, TypeID: %u, Name: %s\n", list[i].id, list[i].base_type_id, list[i].type_id,
		       list[i].name);
		printf("  Set: %u, Binding: %u\n",
		       spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationDescriptorSet),
		       spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding));
	}
}