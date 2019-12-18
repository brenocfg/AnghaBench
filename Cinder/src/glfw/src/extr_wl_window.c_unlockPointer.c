#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zwp_relative_pointer_v1 {int dummy; } ;
struct zwp_locked_pointer_v1 {int dummy; } ;
struct TYPE_5__ {struct zwp_locked_pointer_v1* lockedPointer; struct zwp_relative_pointer_v1* relativePointer; } ;
struct TYPE_6__ {TYPE_1__ pointerLock; } ;
struct TYPE_7__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  zwp_locked_pointer_v1_destroy (struct zwp_locked_pointer_v1*) ; 
 int /*<<< orphan*/  zwp_relative_pointer_v1_destroy (struct zwp_relative_pointer_v1*) ; 

__attribute__((used)) static void unlockPointer(_GLFWwindow* window)
{
    struct zwp_relative_pointer_v1* relativePointer =
        window->wl.pointerLock.relativePointer;
    struct zwp_locked_pointer_v1* lockedPointer =
        window->wl.pointerLock.lockedPointer;

    zwp_relative_pointer_v1_destroy(relativePointer);
    zwp_locked_pointer_v1_destroy(lockedPointer);

    window->wl.pointerLock.relativePointer = NULL;
    window->wl.pointerLock.lockedPointer = NULL;
}