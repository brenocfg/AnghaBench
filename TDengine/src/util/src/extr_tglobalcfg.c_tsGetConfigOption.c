#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  option; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* tsGlobalConfig ; 
 int tsGlobalConfigNum ; 
 int /*<<< orphan*/  tsInitGlobalConfig () ; 

SGlobalConfig *tsGetConfigOption(const char *option) {
  tsInitGlobalConfig();
  for (int i = 0; i < tsGlobalConfigNum; ++i) {
    SGlobalConfig *cfg = tsGlobalConfig + i;
    if (strcasecmp(cfg->option, option) != 0) continue;
    return cfg;
  }
  return NULL;
}