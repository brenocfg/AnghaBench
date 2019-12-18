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
struct TYPE_3__ {int we_wordc; char** we_wordv; scalar_t__ wordPos; scalar_t__ we_offs; } ;
typedef  TYPE_1__ wordexp_t ;

/* Variables and functions */

int wordexp(const char *words, wordexp_t *pwordexp, int flags) {
  pwordexp->we_offs = 0;
  pwordexp->we_wordc = 1;
  pwordexp->we_wordv = (char **)(pwordexp->wordPos);
  pwordexp->we_wordv[0] = (char *)words;
  return 0;
}