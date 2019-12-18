#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct android_app {TYPE_1__* activity; } ;
typedef  double jdouble ;
typedef  int /*<<< orphan*/  jboolean ;
struct TYPE_4__ {int /*<<< orphan*/  onLocationGetHorizontalAccuracy; int /*<<< orphan*/  onLocationGetLongitude; int /*<<< orphan*/  onLocationGetLatitude; int /*<<< orphan*/  onLocationHasChanged; } ;
typedef  TYPE_2__ androidlocation_t ;
struct TYPE_3__ {int /*<<< orphan*/  clazz; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_BOOLEAN_METHOD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALL_DOUBLE_METHOD (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_android ; 
 int /*<<< orphan*/ * jni_thread_getenv () ; 

__attribute__((used)) static bool android_location_get_position(void *data, double *latitude,
      double *longitude, double *horiz_accuracy,
      double *vert_accuracy)
{
   struct android_app *android_app = (struct android_app*)g_android;
   androidlocation_t *androidlocation = (androidlocation_t*)data;
   JNIEnv *env = jni_thread_getenv();
   if (!env)
      goto fail;

   jdouble lat, lon, horiz_accu;
   jboolean newLocation;

   CALL_BOOLEAN_METHOD(env, newLocation, android_app->activity->clazz,
         androidlocation->onLocationHasChanged);

   if (!newLocation)
      goto fail;

   CALL_DOUBLE_METHOD(env, lat,        android_app->activity->clazz,
         androidlocation->onLocationGetLatitude);
   CALL_DOUBLE_METHOD(env, lon,        android_app->activity->clazz,
         androidlocation->onLocationGetLongitude);
   CALL_DOUBLE_METHOD(env, horiz_accu, android_app->activity->clazz,
         androidlocation->onLocationGetHorizontalAccuracy);

   if (lat != 0.0)
      *latitude = lat;
   if (lon != 0.0)
      *longitude = lon;
   if (horiz_accu != 0.0)
      *horiz_accuracy = horiz_accu;

   /* TODO/FIXME - custom implement vertical accuracy since
    * Android location API does not have it? */
   *vert_accuracy = 0.0;

   return true;

fail:
   *latitude  = 0.0;
   *longitude = 0.0;
   *horiz_accuracy  = 0.0;
   *vert_accuracy  = 0.0;
   return false;
}