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
struct TYPE_4__ {size_t characterCount; TYPE_1__* characterList; } ;
struct TYPE_3__ {char const* name; int headImage; void* base; void* imageName; } ;

/* Variables and functions */
 char* COM_ParseExt (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 size_t MAX_HEADS ; 
 scalar_t__ Q_stricmp (char const*,char*) ; 
 void* String_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ uiInfo ; 
 int /*<<< orphan*/  va (char*,...) ; 

__attribute__((used)) static qboolean Character_Parse(char **p) {
  char *token;
  const char *tempStr;

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
      // two tokens per line, character name and sex
      if (!String_Parse(p, &uiInfo.characterList[uiInfo.characterCount].name) || !String_Parse(p, &tempStr)) {
        return qfalse;
      }
    
      uiInfo.characterList[uiInfo.characterCount].headImage = -1;
			uiInfo.characterList[uiInfo.characterCount].imageName = String_Alloc(va("models/players/heads/%s/icon_default.tga", uiInfo.characterList[uiInfo.characterCount].name));

	  if (tempStr && (!Q_stricmp(tempStr, "female"))) {
        uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("Janet"));
      } else if (tempStr && (!Q_stricmp(tempStr, "male"))) {
        uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("James"));
	  } else {
        uiInfo.characterList[uiInfo.characterCount].base = String_Alloc(va("%s",tempStr));
	  }

      Com_Printf("Loaded %s character %s.\n", uiInfo.characterList[uiInfo.characterCount].base, uiInfo.characterList[uiInfo.characterCount].name);
      if (uiInfo.characterCount < MAX_HEADS) {
        uiInfo.characterCount++;
      } else {
        Com_Printf("Too many characters, last character replaced!\n");
      }
     
      token = COM_ParseExt(p, qtrue);
      if (token[0] != '}') {
        return qfalse;
      }
    }
  }

  return qfalse;
}