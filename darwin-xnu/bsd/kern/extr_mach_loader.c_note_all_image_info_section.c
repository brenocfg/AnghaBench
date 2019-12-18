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
struct segment_command_64 {unsigned int nsects; int /*<<< orphan*/  segname; } ;
struct section_64 {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  sectname; } ;
struct section {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  all_image_info_size; int /*<<< orphan*/  all_image_info_addr; } ;
typedef  TYPE_1__ load_result_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
note_all_image_info_section(const struct segment_command_64 *scp,
    boolean_t is64, size_t section_size, const void *sections,
    int64_t slide, load_result_t *result)
{
	const union {
		struct section s32;
		struct section_64 s64;
	} *sectionp;
	unsigned int i;

     
	if (strncmp(scp->segname, "__DATA", sizeof(scp->segname)) != 0)
		return;
	for (i = 0; i < scp->nsects; ++i) {
		sectionp = (const void *)
		    ((const char *)sections + section_size * i);
		if (0 == strncmp(sectionp->s64.sectname, "__all_image_info",
		    sizeof(sectionp->s64.sectname))) {
			result->all_image_info_addr =
			    is64 ? sectionp->s64.addr : sectionp->s32.addr;
			result->all_image_info_addr += slide;
			result->all_image_info_size =
			    is64 ? sectionp->s64.size : sectionp->s32.size;
			return;
		}
	}
}