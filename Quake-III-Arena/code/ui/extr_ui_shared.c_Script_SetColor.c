#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
struct TYPE_4__ {float* backColor; float* foreColor; float* borderColor; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ window; } ;
typedef  TYPE_2__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Float_Parse (char**,float*) ; 
 scalar_t__ Q_stricmp (char const*,char*) ; 
 scalar_t__ String_Parse (char**,char const**) ; 
 int /*<<< orphan*/  WINDOW_BACKCOLORSET ; 
 int /*<<< orphan*/  WINDOW_FORECOLORSET ; 

void Script_SetColor(itemDef_t *item, char **args) {
  const char *name;
  int i;
  float f;
  vec4_t *out;
  // expecting type of color to set and 4 args for the color
  if (String_Parse(args, &name)) {
      out = NULL;
      if (Q_stricmp(name, "backcolor") == 0) {
        out = &item->window.backColor;
        item->window.flags |= WINDOW_BACKCOLORSET;
      } else if (Q_stricmp(name, "forecolor") == 0) {
        out = &item->window.foreColor;
        item->window.flags |= WINDOW_FORECOLORSET;
      } else if (Q_stricmp(name, "bordercolor") == 0) {
        out = &item->window.borderColor;
      }

      if (out) {
        for (i = 0; i < 4; i++) {
          if (!Float_Parse(args, &f)) {
            return;
          }
          (*out)[i] = f;
        }
      }
  }
}