#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  itemDef_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* runScript ) (char**) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ *,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* DC ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char const*) ; 
 scalar_t__ Q_stricmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  String_Parse (char**,char const**) ; 
 TYPE_1__* commandList ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int scriptCommandCount ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  stub2 (char**) ; 

void Item_RunScript(itemDef_t *item, const char *s) {
  char script[1024], *p;
  int i;
  qboolean bRan;
  memset(script, 0, sizeof(script));
  if (item && s && s[0]) {
    Q_strcat(script, 1024, s);
    p = script;
    while (1) {
      const char *command;
      // expect command then arguments, ; ends command, NULL ends script
      if (!String_Parse(&p, &command)) {
        return;
      }

      if (command[0] == ';' && command[1] == '\0') {
        continue;
      }

      bRan = qfalse;
      for (i = 0; i < scriptCommandCount; i++) {
        if (Q_stricmp(command, commandList[i].name) == 0) {
          (commandList[i].handler(item, &p));
          bRan = qtrue;
          break;
        }
      }
      // not in our auto list, pass to handler
      if (!bRan) {
        DC->runScript(&p);
      }
    }
  }
}