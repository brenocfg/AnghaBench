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
struct TYPE_3__ {int dirtyPal; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  PicoLoadStateHook () ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  areaSeek (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int state_load (void*) ; 
 int state_load_legacy (void*) ; 
 int state_save (void*) ; 

__attribute__((used)) static int pico_state_internal(void *afile, int is_save)
{
  int ret;

  if (is_save)
    ret = state_save(afile);
  else {
    ret = state_load(afile);
    if (ret != 0) {
      areaSeek(afile, 0, SEEK_SET);
      ret = state_load_legacy(afile);
    }

    if (PicoLoadStateHook != NULL)
      PicoLoadStateHook();
    Pico.m.dirtyPal = 1;
  }

  return ret;
}