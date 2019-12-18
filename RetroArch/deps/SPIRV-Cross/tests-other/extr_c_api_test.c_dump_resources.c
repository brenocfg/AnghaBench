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
typedef  int /*<<< orphan*/  spvc_resources ;
typedef  int /*<<< orphan*/  spvc_compiler ;

/* Variables and functions */
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_PUSH_CONSTANT ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_SAMPLED_IMAGE ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_SEPARATE_IMAGE ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_SEPARATE_SAMPLERS ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_STAGE_INPUT ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_STAGE_OUTPUT ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_STORAGE_BUFFER ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_STORAGE_IMAGE ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_SUBPASS_INPUT ; 
 int /*<<< orphan*/  SPVC_RESOURCE_TYPE_UNIFORM_BUFFER ; 
 int /*<<< orphan*/  dump_resource_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dump_resources(spvc_compiler compiler, spvc_resources resources)
{
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_UNIFORM_BUFFER, "UBO");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_STORAGE_BUFFER, "SSBO");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_PUSH_CONSTANT, "Push");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_SEPARATE_SAMPLERS, "Samplers");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_SEPARATE_IMAGE, "Image");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_SAMPLED_IMAGE, "Combined image samplers");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_STAGE_INPUT, "Stage input");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_STAGE_OUTPUT, "Stage output");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_STORAGE_IMAGE, "Storage image");
	dump_resource_list(compiler, resources, SPVC_RESOURCE_TYPE_SUBPASS_INPUT, "Subpass input");
}