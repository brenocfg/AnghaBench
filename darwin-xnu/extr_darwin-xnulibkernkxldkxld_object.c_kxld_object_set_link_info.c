#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vmaddr_LINKEDIT; int /*<<< orphan*/  vmaddr_LLVM_COV; int /*<<< orphan*/  vmaddr_DATA_CONST; int /*<<< orphan*/  vmaddr_DATA; int /*<<< orphan*/  vmaddr_TEXT_EXEC; int /*<<< orphan*/  vmaddr_TEXT; } ;
struct TYPE_8__ {int /*<<< orphan*/  vmaddr_LINKEDIT; TYPE_1__ split_info; int /*<<< orphan*/  vmaddr_LLVM_COV; int /*<<< orphan*/  vmaddr_DATA_CONST; int /*<<< orphan*/  vmaddr_DATA; int /*<<< orphan*/  vmaddr_TEXT_EXEC; int /*<<< orphan*/  vmaddr_TEXT; } ;
typedef  TYPE_2__ splitKextLinkInfo ;
typedef  TYPE_2__ KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  check (TYPE_2__*) ; 

void
kxld_object_set_link_info(KXLDObject *object, splitKextLinkInfo *link_info)
{
    check(object);
    check(link_info);

    object->split_info.vmaddr_TEXT = link_info->vmaddr_TEXT;
    object->split_info.vmaddr_TEXT_EXEC = link_info->vmaddr_TEXT_EXEC;
    object->split_info.vmaddr_DATA = link_info->vmaddr_DATA;
    object->split_info.vmaddr_DATA_CONST = link_info->vmaddr_DATA_CONST;
    object->split_info.vmaddr_LLVM_COV = link_info->vmaddr_LLVM_COV;
    object->split_info.vmaddr_LINKEDIT = link_info->vmaddr_LINKEDIT;

    return;
}