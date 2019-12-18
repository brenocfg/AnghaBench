#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ (* malloc_fcn ) (int) ;} ;
typedef  TYPE_2__ XML_Memory_Handling_Suite ;
struct TYPE_8__ {int /*<<< orphan*/ * binding; int /*<<< orphan*/ * name; } ;
struct TYPE_10__ {void* standalone; void* hasParamEntityRefs; int /*<<< orphan*/  keepProcessing; scalar_t__ contentStringLen; scalar_t__ scaffCount; scalar_t__ scaffSize; scalar_t__ scaffLevel; int /*<<< orphan*/ * scaffold; int /*<<< orphan*/ * scaffIndex; void* in_eldecl; TYPE_1__ defaultPrefix; int /*<<< orphan*/  paramEntities; void* paramEntityRead; int /*<<< orphan*/  prefixes; int /*<<< orphan*/  attributeIds; int /*<<< orphan*/  elementTypes; int /*<<< orphan*/  generalEntities; int /*<<< orphan*/  entityValuePool; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ DTD ;

/* Variables and functions */
 void* XML_FALSE ; 
 int /*<<< orphan*/  XML_TRUE ; 
 int /*<<< orphan*/  hashTableInit (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  poolInit (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 scalar_t__ stub1 (int) ; 

__attribute__((used)) static DTD *
dtdCreate(const XML_Memory_Handling_Suite *ms)
{
  DTD *p = (DTD *)ms->malloc_fcn(sizeof(DTD));
  if (p == NULL)
    return p;
  poolInit(&(p->pool), ms);
  poolInit(&(p->entityValuePool), ms);
  hashTableInit(&(p->generalEntities), ms);
  hashTableInit(&(p->elementTypes), ms);
  hashTableInit(&(p->attributeIds), ms);
  hashTableInit(&(p->prefixes), ms);
#ifdef XML_DTD
  p->paramEntityRead = XML_FALSE;
  hashTableInit(&(p->paramEntities), ms);
#endif /* XML_DTD */
  p->defaultPrefix.name = NULL;
  p->defaultPrefix.binding = NULL;

  p->in_eldecl = XML_FALSE;
  p->scaffIndex = NULL;
  p->scaffold = NULL;
  p->scaffLevel = 0;
  p->scaffSize = 0;
  p->scaffCount = 0;
  p->contentStringLen = 0;

  p->keepProcessing = XML_TRUE;
  p->hasParamEntityRefs = XML_FALSE;
  p->standalone = XML_FALSE;
  return p;
}