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
typedef  int /*<<< orphan*/  XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;
typedef  scalar_t__ XML_Bool ;
struct TYPE_9__ {int /*<<< orphan*/  maybeTokenized; int /*<<< orphan*/  xmlns; } ;
struct TYPE_8__ {scalar_t__ isCdata; int /*<<< orphan*/  const* value; TYPE_3__* id; } ;
struct TYPE_7__ {int nDefaultAtts; int allocDefaultAtts; TYPE_2__* defaultAtts; TYPE_3__* idAtt; } ;
typedef  TYPE_1__ ELEMENT_TYPE ;
typedef  TYPE_2__ DEFAULT_ATTRIBUTE ;
typedef  TYPE_3__ ATTRIBUTE_ID ;

/* Variables and functions */
 scalar_t__ MALLOC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ REALLOC (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  XML_TRUE ; 

__attribute__((used)) static int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *attId, XML_Bool isCdata,
                XML_Bool isId, const XML_Char *value, XML_Parser parser)
{
  DEFAULT_ATTRIBUTE *att;
  if (value || isId) {
    /* The handling of default attributes gets messed up if we have
       a default which duplicates a non-default. */
    int i;
    for (i = 0; i < type->nDefaultAtts; i++)
      if (attId == type->defaultAtts[i].id)
        return 1;
    if (isId && !type->idAtt && !attId->xmlns)
      type->idAtt = attId;
  }
  if (type->nDefaultAtts == type->allocDefaultAtts) {
    if (type->allocDefaultAtts == 0) {
      type->allocDefaultAtts = 8;
      type->defaultAtts = (DEFAULT_ATTRIBUTE *)MALLOC(parser, type->allocDefaultAtts
                            * sizeof(DEFAULT_ATTRIBUTE));
      if (!type->defaultAtts) {
        type->allocDefaultAtts = 0;
        return 0;
      }
    }
    else {
      DEFAULT_ATTRIBUTE *temp;
      int count = type->allocDefaultAtts * 2;
      temp = (DEFAULT_ATTRIBUTE *)
        REALLOC(parser, type->defaultAtts, (count * sizeof(DEFAULT_ATTRIBUTE)));
      if (temp == NULL)
        return 0;
      type->allocDefaultAtts = count;
      type->defaultAtts = temp;
    }
  }
  att = type->defaultAtts + type->nDefaultAtts;
  att->id = attId;
  att->value = value;
  att->isCdata = isCdata;
  if (!isCdata)
    attId->maybeTokenized = XML_TRUE;
  type->nDefaultAtts += 1;
  return 1;
}