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
typedef  scalar_t__ qboolean ;
struct TYPE_2__ {int realTime; } ;

/* Variables and functions */
 TYPE_1__* DC ; 
 int WINDOW_FADINGIN ; 
 int WINDOW_FADINGOUT ; 
 int WINDOW_VISIBLE ; 

void Fade(int *flags, float *f, float clamp, int *nextTime, int offsetTime, qboolean bFlags, float fadeAmount) {
  if (*flags & (WINDOW_FADINGOUT | WINDOW_FADINGIN)) {
    if (DC->realTime > *nextTime) {
      *nextTime = DC->realTime + offsetTime;
      if (*flags & WINDOW_FADINGOUT) {
        *f -= fadeAmount;
        if (bFlags && *f <= 0.0) {
          *flags &= ~(WINDOW_FADINGOUT | WINDOW_VISIBLE);
        }
      } else {
        *f += fadeAmount;
        if (*f >= clamp) {
          *f = clamp;
          if (bFlags) {
            *flags &= ~WINDOW_FADINGIN;
          }
        }
      }
    }
  }
}