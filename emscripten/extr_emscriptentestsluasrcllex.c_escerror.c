#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buff; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int EOZ ; 
 int /*<<< orphan*/  TK_STRING ; 
 int /*<<< orphan*/  lexerror (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_resetbuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save (TYPE_1__*,int) ; 

__attribute__((used)) static void escerror (LexState *ls, int *c, int n, const char *msg) {
  int i;
  luaZ_resetbuffer(ls->buff);  /* prepare error message */
  save(ls, '\\');
  for (i = 0; i < n && c[i] != EOZ; i++)
    save(ls, c[i]);
  lexerror(ls, msg, TK_STRING);
}