#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  process; struct android_app* app; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  process; struct android_app* app; int /*<<< orphan*/  id; } ;
struct android_app {int running; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/ * looper; TYPE_3__ cmdPollSource; int /*<<< orphan*/  msgread; TYPE_2__ inputPollSource; TYPE_1__* activity; int /*<<< orphan*/  config; } ;
struct TYPE_4__ {int /*<<< orphan*/  assetManager; } ;
typedef  int /*<<< orphan*/  ALooper ;

/* Variables and functions */
 int /*<<< orphan*/  AConfiguration_fromAssetManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AConfiguration_new () ; 
 int /*<<< orphan*/  ALOOPER_EVENT_INPUT ; 
 int /*<<< orphan*/  ALOOPER_PREPARE_ALLOW_NON_CALLBACKS ; 
 int /*<<< orphan*/  ALooper_addFd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * ALooper_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOPER_ID_INPUT ; 
 int /*<<< orphan*/  LOOPER_ID_MAIN ; 
 int /*<<< orphan*/  android_app_destroy (struct android_app*) ; 
 int /*<<< orphan*/  android_main (struct android_app*) ; 
 int /*<<< orphan*/  print_cur_config (struct android_app*) ; 
 int /*<<< orphan*/  process_cmd ; 
 int /*<<< orphan*/  process_input ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* android_app_entry(void* param) {
    struct android_app* android_app = (struct android_app*)param;

    android_app->config = AConfiguration_new();
    AConfiguration_fromAssetManager(android_app->config, android_app->activity->assetManager);

    print_cur_config(android_app);

    android_app->cmdPollSource.id = LOOPER_ID_MAIN;
    android_app->cmdPollSource.app = android_app;
    android_app->cmdPollSource.process = process_cmd;
    android_app->inputPollSource.id = LOOPER_ID_INPUT;
    android_app->inputPollSource.app = android_app;
    android_app->inputPollSource.process = process_input;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    ALooper_addFd(looper, android_app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
            &android_app->cmdPollSource);
    android_app->looper = looper;

    pthread_mutex_lock(&android_app->mutex);
    android_app->running = 1;
    pthread_cond_broadcast(&android_app->cond);
    pthread_mutex_unlock(&android_app->mutex);

    android_main(android_app);

    android_app_destroy(android_app);

    // In the case where the activity successfully gets destroyed (on config changes)
    // this will cause the destructors setup using pthread_key_create to fire.
    pthread_exit((void*)NULL);
    return NULL;
}