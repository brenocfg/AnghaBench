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
struct ldfile {int /*<<< orphan*/  bss_addr; int /*<<< orphan*/  data_addr; int /*<<< orphan*/  txt_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  vx_add_symbols (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_symbol_stub (char *arg)
{
  struct ldfile *pLoadFile = (struct ldfile *) arg;

  printf_unfiltered ("\t%s: ", pLoadFile->name);
  vx_add_symbols (pLoadFile->name, 0, pLoadFile->txt_addr,
		  pLoadFile->data_addr, pLoadFile->bss_addr);
  printf_unfiltered ("ok\n");
  return 1;
}