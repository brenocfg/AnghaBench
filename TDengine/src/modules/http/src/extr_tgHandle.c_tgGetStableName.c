#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ cJSON ;
struct TYPE_9__ {int size; TYPE_2__* schemas; } ;
struct TYPE_8__ {int fieldNum; char** fields; char* tbName; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ STgSchema ;

/* Variables and functions */
 TYPE_1__* cJSON_GetArrayItem (TYPE_1__*,int) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ tgSchemas ; 

char *tgGetStableName(char *stname, cJSON *fields, int fieldsSize) {
  for (int s = 0; s < tgSchemas.size; ++s) {
    STgSchema *schema = &tgSchemas.schemas[s];
    if (strcasecmp(schema->name, stname) != 0) {
      continue;
    }

    bool schemaMatched = true;
    for (int f = 0; f < schema->fieldNum; ++f) {
      char *fieldName = schema->fields[f];
      bool fieldMatched = false;

      for (int i = 0; i < fieldsSize; i++) {
        cJSON *field = cJSON_GetArrayItem(fields, i);
        if (strcasecmp(field->string, fieldName) == 0) {
          fieldMatched = true;
          break;
        }
      }

      if (!fieldMatched) {
        schemaMatched = false;
        break;
      }
    }

    if (schemaMatched) {
      return schema->tbName;
    }
  }

  return stname;
}