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
struct TYPE_3__ {double accelerationX; double accelerationY; double accelerationZ; double accelerationIncludingGravityX; double accelerationIncludingGravityY; double accelerationIncludingGravityZ; double rotationRateAlpha; double rotationRateBeta; double rotationRateGamma; } ;
typedef  TYPE_1__ EmscriptenDeviceMotionEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 char* emscripten_event_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,char*,double,double,double,double,double,double,double,double,double) ; 

EM_BOOL devicemotion_callback(int eventType, const EmscriptenDeviceMotionEvent *e, void *userData)
{
  printf("%s, accel: (%g, %g, %g), accelInclGravity: (%g, %g, %g), rotationRate: (%g, %g, %g)\n", 
    emscripten_event_type_to_string(eventType), 
    e->accelerationX, e->accelerationY, e->accelerationZ,
    e->accelerationIncludingGravityX, e->accelerationIncludingGravityY, e->accelerationIncludingGravityZ,
    e->rotationRateAlpha, e->rotationRateBeta, e->rotationRateGamma);

  return 0;
}