#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int size; int uniformBlockCount; int uniformVarCount; int initialValueCount; int loopVarCount; int samplerVarCount; int attribVarCount; TYPE_6__* attribVars; TYPE_5__* samplerVars; TYPE_4__* loopVars; TYPE_3__* initialValues; TYPE_2__* uniformVars; TYPE_1__* uniformBlocks; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int location; int count; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int type; int location; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int offset; int /*<<< orphan*/  value; } ;
struct TYPE_11__ {int offset; int /*<<< orphan*/ * value; } ;
struct TYPE_10__ {int offset; int type; int count; int block; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int offset; int size; int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ GX2VertexShader ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_FLOAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_INT (int) ; 
 int /*<<< orphan*/  DEBUG_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_VAR (int /*<<< orphan*/ ) ; 

void dump_vs_data(GX2VertexShader* vs)
{

   DEBUG_INT(vs->size);
   DEBUG_VAR(vs->mode);
   DEBUG_INT(vs->uniformBlockCount);
   for(int i = 0; i < vs->uniformBlockCount; i++)
   {
      DEBUG_STR(vs->uniformBlocks[i].name);
      DEBUG_INT(vs->uniformBlocks[i].offset);
      DEBUG_INT(vs->uniformBlocks[i].size);
   }
   DEBUG_INT(vs->uniformVarCount);
   for(int i = 0; i < vs->uniformVarCount; i++)
   {
      DEBUG_STR(vs->uniformVars[i].name);
      DEBUG_INT(vs->uniformVars[i].offset);
      DEBUG_INT(vs->uniformVars[i].type);
      DEBUG_INT(vs->uniformVars[i].count);
      DEBUG_INT(vs->uniformVars[i].block);
   }
   DEBUG_INT(vs->initialValueCount);
   for(int i = 0; i < vs->initialValueCount; i++)
   {
      DEBUG_INT(vs->initialValues[i].offset);
      DEBUG_FLOAT(vs->initialValues[i].value[0]);
      DEBUG_FLOAT(vs->initialValues[i].value[1]);
      DEBUG_FLOAT(vs->initialValues[i].value[2]);
      DEBUG_FLOAT(vs->initialValues[i].value[3]);
   }
   DEBUG_INT(vs->loopVarCount);
   for(int i = 0; i < vs->loopVarCount; i++)
   {
      DEBUG_INT(vs->loopVars[i].offset);
      DEBUG_VAR(vs->loopVars[i].value);
   }
   DEBUG_INT(vs->samplerVarCount);
   for(int i = 0; i < vs->samplerVarCount; i++)
   {
      DEBUG_STR(vs->samplerVars[i].name);
      DEBUG_INT(vs->samplerVars[i].type);
      DEBUG_INT(vs->samplerVars[i].location);
   }

   for(int i = 0; i < vs->attribVarCount; i++)
   {
      DEBUG_STR(vs->attribVars[i].name);
      DEBUG_VAR(vs->attribVars[i].type);
      DEBUG_INT(vs->attribVars[i].location);
      DEBUG_INT(vs->attribVars[i].count);
   }
}