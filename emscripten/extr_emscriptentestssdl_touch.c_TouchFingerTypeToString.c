#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SDL_FINGERDOWN ; 
 int SDL_FINGERMOTION ; 
 int SDL_FINGERUP ; 

__attribute__((used)) static char *TouchFingerTypeToString(int type) {
  if (type == SDL_FINGERMOTION) return "SDL_FINGERMOTION";
  if (type == SDL_FINGERDOWN) return "SDL_FINGERDOWN";
  if (type == SDL_FINGERUP) return "SDL_FINGERUP";
  return "UNKNOWN";
}