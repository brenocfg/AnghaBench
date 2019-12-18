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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_2__ {int /*<<< orphan*/  preset; int /*<<< orphan*/  filter_id; } ;
typedef  TYPE_1__ filter_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  filter_opts_set2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filter_opts_set(signal_user_data_t *ud, const gchar *name,
                void *vopts, const void* data)
{
    filter_opts_t *opts = (filter_opts_t*)vopts;

    (void)data; // Silence "unused variable" warning
    filter_opts_set2(ud, name, opts->filter_id, opts->preset);
}