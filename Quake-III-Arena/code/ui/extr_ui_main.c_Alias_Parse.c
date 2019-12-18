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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {size_t aliasCount; TYPE_1__* aliasList; } ;
struct TYPE_3__ {int /*<<< orphan*/  ai; int /*<<< orphan*/  name; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 char* COM_ParseExt (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 size_t MAX_ALIASES ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  String_Parse (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static qboolean Alias_Parse(char **p) {
  char *token;

  token = COM_ParseExt(p, qtrue);

  if (token[0] != '{') {
    return qfalse;
  }

  while ( 1 ) {
    token = COM_ParseExt(p, qtrue);

    if (Q_stricmp(token, "}") == 0) {
      return qtrue;
    }

    if ( !token || token[0] == 0 ) {
      return qfalse;
    }

    if (token[0] == '{') {
      // three tokens per line, character name, bot alias, and preferred action a - all purpose, d - defense, o - offense
      if (!String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].name) || !String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].ai) || !String_Parse(p, &uiInfo.aliasList[uiInfo.aliasCount].action)) {
        return qfalse;
      }
    
      Com_Printf("Loaded character alias %s using character ai %s.\n", uiInfo.aliasList[uiInfo.aliasCount].name, uiInfo.aliasList[uiInfo.aliasCount].ai);
      if (uiInfo.aliasCount < MAX_ALIASES) {
        uiInfo.aliasCount++;
      } else {
        Com_Printf("Too many aliases, last alias replaced!\n");
      }
     
      token = COM_ParseExt(p, qtrue);
      if (token[0] != '}') {
        return qfalse;
      }
    }
  }

  return qfalse;
}