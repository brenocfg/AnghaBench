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
struct TYPE_2__ {int /*<<< orphan*/  search_path; } ;

/* Variables and functions */
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int
gopt_search_path(const char *val)
{
  gopt.search_path = xstrdup(val);
  return 0;
}