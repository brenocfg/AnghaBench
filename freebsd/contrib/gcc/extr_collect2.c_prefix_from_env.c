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
struct path_prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ENVIRONMENT (char const*,char const*) ; 
 int /*<<< orphan*/  prefix_from_string (char const*,struct path_prefix*) ; 

__attribute__((used)) static void
prefix_from_env (const char *env, struct path_prefix *pprefix)
{
  const char *p;
  GET_ENVIRONMENT (p, env);

  if (p)
    prefix_from_string (p, pprefix);
}