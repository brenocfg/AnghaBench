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
struct TYPE_2__ {scalar_t__ binding; } ;

/* Variables and functions */
 scalar_t__ Q_stricmp (char const*,scalar_t__) ; 
 TYPE_1__* keys ; 

int Key_GetKey(const char *binding) {
  int i;

  if (binding) {
  	for (i=0 ; i<256 ; i++) {
      if (keys[i].binding && Q_stricmp(binding, keys[i].binding) == 0) {
        return i;
      }
    }
  }
  return -1;
}