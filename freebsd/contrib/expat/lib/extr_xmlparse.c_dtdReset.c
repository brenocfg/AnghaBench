#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* free_fcn ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ XML_Memory_Handling_Suite ;
struct TYPE_7__ {int /*<<< orphan*/ * binding; int /*<<< orphan*/ * name; } ;
struct TYPE_10__ {void* standalone; void* hasParamEntityRefs; int /*<<< orphan*/  keepProcessing; scalar_t__ contentStringLen; scalar_t__ scaffCount; scalar_t__ scaffSize; scalar_t__ scaffLevel; int /*<<< orphan*/ * scaffold; int /*<<< orphan*/ * scaffIndex; void* in_eldecl; TYPE_1__ defaultPrefix; int /*<<< orphan*/  entityValuePool; int /*<<< orphan*/  pool; int /*<<< orphan*/  prefixes; int /*<<< orphan*/  attributeIds; int /*<<< orphan*/  elementTypes; int /*<<< orphan*/  paramEntities; void* paramEntityRead; int /*<<< orphan*/  generalEntities; } ;
struct TYPE_9__ {scalar_t__ allocDefaultAtts; int /*<<< orphan*/ * defaultAtts; } ;
typedef  int /*<<< orphan*/  HASH_TABLE_ITER ;
typedef  TYPE_3__ ELEMENT_TYPE ;
typedef  TYPE_4__ DTD ;

/* Variables and functions */
 void* XML_FALSE ; 
 int /*<<< orphan*/  XML_TRUE ; 
 int /*<<< orphan*/  hashTableClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashTableIterInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hashTableIterNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poolClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtdReset(DTD *p, const XML_Memory_Handling_Suite *ms)
{
  HASH_TABLE_ITER iter;
  hashTableIterInit(&iter, &(p->elementTypes));
  for (;;) {
    ELEMENT_TYPE *e = (ELEMENT_TYPE *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (e->allocDefaultAtts != 0)
      ms->free_fcn(e->defaultAtts);
  }
  hashTableClear(&(p->generalEntities));
#ifdef XML_DTD
  p->paramEntityRead = XML_FALSE;
  hashTableClear(&(p->paramEntities));
#endif /* XML_DTD */
  hashTableClear(&(p->elementTypes));
  hashTableClear(&(p->attributeIds));
  hashTableClear(&(p->prefixes));
  poolClear(&(p->pool));
  poolClear(&(p->entityValuePool));
  p->defaultPrefix.name = NULL;
  p->defaultPrefix.binding = NULL;

  p->in_eldecl = XML_FALSE;

  ms->free_fcn(p->scaffIndex);
  p->scaffIndex = NULL;
  ms->free_fcn(p->scaffold);
  p->scaffold = NULL;

  p->scaffLevel = 0;
  p->scaffSize = 0;
  p->scaffCount = 0;
  p->contentStringLen = 0;

  p->keepProcessing = XML_TRUE;
  p->hasParamEntityRefs = XML_FALSE;
  p->standalone = XML_FALSE;
}