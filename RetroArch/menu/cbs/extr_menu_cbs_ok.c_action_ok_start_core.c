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
struct TYPE_3__ {int /*<<< orphan*/ * environ_get; int /*<<< orphan*/ * args; int /*<<< orphan*/ * argv; scalar_t__ argc; } ;
typedef  TYPE_1__ content_ctx_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_start_current_core (TYPE_1__*) ; 

__attribute__((used)) static int action_ok_start_core(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   content_ctx_info_t content_info;

   content_info.argc                   = 0;
   content_info.argv                   = NULL;
   content_info.args                   = NULL;
   content_info.environ_get            = NULL;

   path_clear(RARCH_PATH_BASENAME);
   if (!task_push_start_current_core(&content_info))
      return -1;

   return 0;
}