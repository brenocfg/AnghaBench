#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct android_app {int activityState; int destroyRequested; TYPE_1__* activity; int /*<<< orphan*/  config; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  pendingWindow; int /*<<< orphan*/  window; int /*<<< orphan*/  inputPollSource; int /*<<< orphan*/  looper; int /*<<< orphan*/ * inputQueue; int /*<<< orphan*/ * pendingInputQueue; } ;
typedef  int int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  assetManager; } ;

/* Variables and functions */
 int /*<<< orphan*/  AConfiguration_fromAssetManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AInputQueue_attachLooper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AInputQueue_detachLooper (int /*<<< orphan*/ *) ; 
#define  APP_CMD_CONFIG_CHANGED 136 
#define  APP_CMD_DESTROY 135 
#define  APP_CMD_INIT_WINDOW 134 
#define  APP_CMD_INPUT_CHANGED 133 
#define  APP_CMD_PAUSE 132 
#define  APP_CMD_RESUME 131 
#define  APP_CMD_START 130 
#define  APP_CMD_STOP 129 
#define  APP_CMD_TERM_WINDOW 128 
 int /*<<< orphan*/  LOGV (char*) ; 
 int /*<<< orphan*/  LOOPER_ID_INPUT ; 
 int /*<<< orphan*/  print_cur_config (struct android_app*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd) {
    switch (cmd) {
        case APP_CMD_INPUT_CHANGED:
            //LOGV("APP_CMD_INPUT_CHANGED\n");
            pthread_mutex_lock(&android_app->mutex);
            if (android_app->inputQueue != NULL) {
                AInputQueue_detachLooper(android_app->inputQueue);
            }
            android_app->inputQueue = android_app->pendingInputQueue;
            if (android_app->inputQueue != NULL) {
                LOGV("Attaching input queue to looper");
                AInputQueue_attachLooper(android_app->inputQueue,
                        android_app->looper, LOOPER_ID_INPUT, NULL,
                        &android_app->inputPollSource);
            }
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_INIT_WINDOW:
            //LOGV("APP_CMD_INIT_WINDOW\n");
            pthread_mutex_lock(&android_app->mutex);
            android_app->window = android_app->pendingWindow;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_TERM_WINDOW:
            //LOGV("APP_CMD_TERM_WINDOW\n");
            pthread_cond_broadcast(&android_app->cond);
            break;

        case APP_CMD_RESUME:
        case APP_CMD_START:
        case APP_CMD_PAUSE:
        case APP_CMD_STOP:
            //LOGV("activityState=%d\n", cmd);
            pthread_mutex_lock(&android_app->mutex);
            android_app->activityState = cmd;
            pthread_cond_broadcast(&android_app->cond);
            pthread_mutex_unlock(&android_app->mutex);
            break;

        case APP_CMD_CONFIG_CHANGED:
            //LOGV("APP_CMD_CONFIG_CHANGED\n");
            AConfiguration_fromAssetManager(android_app->config,
                    android_app->activity->assetManager);
            print_cur_config(android_app);
            break;

        case APP_CMD_DESTROY:
            //LOGV("APP_CMD_DESTROY\n");
            android_app->destroyRequested = 1;
            break;
    }
}