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
struct pex_obj {int dummy; } ;

/* Variables and functions */
 int PEX_USE_PIPES ; 
 int /*<<< orphan*/  funcs ; 
 struct pex_obj* pex_init_common (int,char const*,char const*,int /*<<< orphan*/ *) ; 

struct pex_obj *
pex_init (int flags, const char *pname, const char *tempbase)
{
  /* DJGPP does not support pipes.  */
  flags &= ~ PEX_USE_PIPES;
  return pex_init_common (flags, pname, tempbase, &funcs);
}