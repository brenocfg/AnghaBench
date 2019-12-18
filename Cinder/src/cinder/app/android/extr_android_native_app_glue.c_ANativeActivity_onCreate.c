#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  instance; TYPE_1__* callbacks; } ;
struct TYPE_6__ {int /*<<< orphan*/  onLowMemory; int /*<<< orphan*/  onConfigurationChanged; int /*<<< orphan*/  onInputQueueDestroyed; int /*<<< orphan*/  onInputQueueCreated; int /*<<< orphan*/  onNativeWindowDestroyed; int /*<<< orphan*/  onNativeWindowCreated; int /*<<< orphan*/  onWindowFocusChanged; int /*<<< orphan*/  onDestroy; int /*<<< orphan*/  onStop; int /*<<< orphan*/  onPause; int /*<<< orphan*/  onSaveInstanceState; int /*<<< orphan*/  onResume; int /*<<< orphan*/  onStart; } ;
typedef  TYPE_2__ ANativeActivity ;

/* Variables and functions */
 int /*<<< orphan*/  LOGV (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  android_app_create (TYPE_2__*,void*,size_t) ; 
 int /*<<< orphan*/  onConfigurationChanged ; 
 int /*<<< orphan*/  onDestroy ; 
 int /*<<< orphan*/  onInputQueueCreated ; 
 int /*<<< orphan*/  onInputQueueDestroyed ; 
 int /*<<< orphan*/  onLowMemory ; 
 int /*<<< orphan*/  onNativeWindowCreated ; 
 int /*<<< orphan*/  onNativeWindowDestroyed ; 
 int /*<<< orphan*/  onPause ; 
 int /*<<< orphan*/  onResume ; 
 int /*<<< orphan*/  onSaveInstanceState ; 
 int /*<<< orphan*/  onStart ; 
 int /*<<< orphan*/  onStop ; 
 int /*<<< orphan*/  onWindowFocusChanged ; 

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
    LOGV("ANativeActivity_onCreate: %p\n", activity);

    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;

/*    
    activity->callbacks->onDestroy = onDestroy;
    activity->callbacks->onStart = onStart;
    activity->callbacks->onResume = onResume;
    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onPause = onPause;
    activity->callbacks->onStop = onStop;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;
    activity->callbacks->onLowMemory = onLowMemory;
    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;
*/
    activity->instance = android_app_create(activity, savedState, savedStateSize);
}