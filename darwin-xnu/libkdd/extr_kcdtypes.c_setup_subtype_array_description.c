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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kctype_subtype_t ;
typedef  TYPE_1__* kcdata_subtype_descriptor_t ;
struct TYPE_3__ {char* kcs_name; int /*<<< orphan*/  kcs_elem_size; int /*<<< orphan*/  kcs_elem_offset; int /*<<< orphan*/  kcs_elem_type; int /*<<< orphan*/  kcs_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCS_SUBTYPE_FLAGS_ARRAY ; 
 int /*<<< orphan*/  KCS_SUBTYPE_PACK_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_kctype_subtype_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
setup_subtype_array_description(
    kcdata_subtype_descriptor_t desc, kctype_subtype_t type, uint32_t offset, uint32_t count, char * name)
{
	desc->kcs_flags       = KCS_SUBTYPE_FLAGS_ARRAY;
	desc->kcs_elem_type   = type;
	desc->kcs_elem_offset = offset;
	desc->kcs_elem_size = KCS_SUBTYPE_PACK_SIZE(count, get_kctype_subtype_size(type));
	memcpy(desc->kcs_name, name, sizeof(desc->kcs_name));
	desc->kcs_name[sizeof(desc->kcs_name) - 1] = '\0';
}