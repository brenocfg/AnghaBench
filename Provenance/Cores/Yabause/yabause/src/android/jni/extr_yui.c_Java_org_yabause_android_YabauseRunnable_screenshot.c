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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_3__ {int height; int width; int /*<<< orphan*/  stride; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ AndroidBitmapInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AndroidBitmap_getInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AndroidBitmap_lockPixels (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  AndroidBitmap_unlockPixels (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dispbuffer ; 
 int /*<<< orphan*/  g_buf_width ; 

void
Java_org_yabause_android_YabauseRunnable_screenshot( JNIEnv* env, jobject obj, jobject bitmap )
{
    u32 * buffer;
    AndroidBitmapInfo info;
    void * pixels;
    int x, y;

    AndroidBitmap_getInfo(env, bitmap, &info);

    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    buffer = dispbuffer;

    for(y = 0;y < info.height;y++) {
        for(x = 0;x < info.width;x++) {
            *((uint32_t *) pixels + x) = *(buffer + x);
        }
        pixels += info.stride;
        buffer += g_buf_width;
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}