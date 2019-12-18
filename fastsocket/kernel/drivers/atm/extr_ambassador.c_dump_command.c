#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * par; } ;
struct TYPE_6__ {TYPE_1__ args; int /*<<< orphan*/  request; } ;
typedef  TYPE_2__ command ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CMD ; 
 int /*<<< orphan*/  PRINTDB (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTDE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRINTDM (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_command (command * cmd) {
#ifdef DEBUG_AMBASSADOR
  unsigned int i;
  PRINTDB (DBG_CMD, "cmd @ %p, req: %08x, pars:",
	   cmd, /*be32_to_cpu*/ (cmd->request));
  for (i = 0; i < 3; ++i)
    PRINTDM (DBG_CMD, " %08x", /*be32_to_cpu*/ (cmd->args.par[i]));
  PRINTDE (DBG_CMD, "");
#else
  (void) cmd;
#endif
  return;
}