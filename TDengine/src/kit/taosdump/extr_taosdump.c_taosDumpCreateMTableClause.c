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
struct arguments {int dummy; } ;
struct TYPE_5__ {char* name; TYPE_1__* cols; } ;
struct TYPE_4__ {char* note; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ STableDef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* buffer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

void taosDumpCreateMTableClause(STableDef *tableDes, char *metric, int numOfCols, struct arguments *arguments,
                                FILE *fp) {
  char *pstr = NULL;
  pstr = buffer;
  int counter = 0;
  int count_temp = 0;

  pstr += sprintf(buffer, "CREATE TABLE IF NOT EXISTS %s USING %s TAGS (", tableDes->name, metric);

  for (; counter < numOfCols; counter++) {
    if (tableDes->cols[counter].note[0] != '\0') break;
  }

  assert(counter < numOfCols);
  count_temp = counter;

  for (; counter < numOfCols; counter++) {
    if (counter != count_temp) {
      if (strcasecmp(tableDes->cols[counter].type, "binary") == 0 ||
          strcasecmp(tableDes->cols[counter].type, "nchar") == 0) {
        pstr += sprintf(pstr, ", \'%s\'", tableDes->cols[counter].note);
      } else {
        pstr += sprintf(pstr, ", %s", tableDes->cols[counter].note);
      }
    } else {
      if (strcasecmp(tableDes->cols[counter].type, "binary") == 0 ||
          strcasecmp(tableDes->cols[counter].type, "nchar") == 0) {
        pstr += sprintf(pstr, "\'%s\'", tableDes->cols[counter].note);
      } else {
        pstr += sprintf(pstr, "%s", tableDes->cols[counter].note);
      }
      /* pstr += sprintf(pstr, "%s", tableDes->cols[counter].note); */
    }

    /* if (strcasecmp(tableDes->cols[counter].type, "binary") == 0 || strcasecmp(tableDes->cols[counter].type, "nchar")
     * == 0) { */
    /*     pstr += sprintf(pstr, "(%d)", tableDes->cols[counter].length); */
    /* } */
  }

  pstr += sprintf(pstr, ")");

  fprintf(fp, "%s\n\n", buffer);
}