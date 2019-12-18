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
struct TYPE_6__ {int size; } ;

/* Variables and functions */
#define  ARCH_X64 132 
#define  ARCH_X86 131 
#define  OS_LINUX 130 
#define  OS_OSX 129 
#define  OS_WIN32 128 
 size_t TYPE_PTR ; 
 char** arch_names ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* ilp32_metrics ; 
 TYPE_1__* lp64_metrics ; 
 char** os_names ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int target_arch ; 
 int target_os ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  type_llong ; 
 TYPE_1__* type_metrics ; 
 int /*<<< orphan*/  type_ssize ; 
 void* type_uint ; 
 void* type_uintptr ; 
 void* type_ullong ; 
 void* type_usize ; 
 TYPE_1__* win32_x64_metrics ; 
 TYPE_1__* win32_x86_metrics ; 

void init_target(void) {
    type_metrics = NULL;
    switch (target_os) {
    case OS_WIN32:
        switch (target_arch) {
        case ARCH_X86:
            type_metrics = win32_x86_metrics;
            break;
        case ARCH_X64:
            type_metrics = win32_x64_metrics;
            break;
        default:
            break;
        }
        break;
    case OS_LINUX:
        switch (target_arch) {
        case ARCH_X86:
            type_metrics = ilp32_metrics;
            break;
        case ARCH_X64:
            type_metrics = lp64_metrics;
            break;
        default:
            break;
        }
        break;
    case OS_OSX:
        switch (target_arch) {
        case ARCH_X64:
            type_metrics = lp64_metrics;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    if (!type_metrics) {
        printf("Unsupported os/arch combination: %s/%s\n", os_names[target_os], arch_names[target_arch]);
        exit(1);
    }
    if (type_metrics[TYPE_PTR].size == 4) {
        type_uintptr = type_uint;
        type_usize = type_uint;
        type_ssize = type_int;
    } else {
        assert(type_metrics[TYPE_PTR].size == 8);
        type_uintptr = type_ullong;
        type_usize = type_ullong;
        type_ssize = type_llong;
    }
}