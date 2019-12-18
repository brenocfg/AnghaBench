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
struct TYPE_2__ {int /*<<< orphan*/  preset; int /*<<< orphan*/  filter_id; } ;
typedef  TYPE_1__ filter_opts_t ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GhbType ;

/* Variables and functions */
 int /*<<< orphan*/ * filter_opt_get2 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GhbValue *
filter_opt_get(const char *name, const void *vopts,
               const GhbValue *gval, GhbType type)
{
    filter_opts_t *opts = (filter_opts_t*)vopts;
    return filter_opt_get2(name, gval, type, opts->filter_id, opts->preset);
}