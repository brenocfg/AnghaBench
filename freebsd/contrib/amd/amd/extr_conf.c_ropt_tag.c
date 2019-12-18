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
struct TYPE_3__ {int /*<<< orphan*/  cfm_tag; } ;
typedef  TYPE_1__ cf_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int
ropt_tag(const char *val, cf_map_t *cfm)
{
  cfm->cfm_tag = xstrdup(val);
  return 0;
}