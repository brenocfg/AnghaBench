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
struct deps {int dummy; } ;
struct deferred_opt {scalar_t__ code; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 scalar_t__ OPT_MQ ; 
 scalar_t__ OPT_MT ; 
 struct deps* cpp_get_deps (int /*<<< orphan*/ ) ; 
 size_t deferred_count ; 
 struct deferred_opt* deferred_opts ; 
 int /*<<< orphan*/  deps_add_target (struct deps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  deps_seen ; 
 int /*<<< orphan*/  parse_in ; 

__attribute__((used)) static void
handle_deferred_opts (void)
{
  size_t i;
  struct deps *deps;

  /* Avoid allocating the deps buffer if we don't need it.
     (This flag may be true without there having been -MT or -MQ
     options, but we'll still need the deps buffer.)  */
  if (!deps_seen)
    return;

  deps = cpp_get_deps (parse_in);

  for (i = 0; i < deferred_count; i++)
    {
      struct deferred_opt *opt = &deferred_opts[i];

      if (opt->code == OPT_MT || opt->code == OPT_MQ)
	deps_add_target (deps, opt->arg, opt->code == OPT_MQ);
    }
}