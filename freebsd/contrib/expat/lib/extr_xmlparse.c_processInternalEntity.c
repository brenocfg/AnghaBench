#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;
typedef  TYPE_2__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Bool ;
struct TYPE_13__ {int processed; int /*<<< orphan*/  open; scalar_t__ is_param; scalar_t__ textLen; scalar_t__ textPtr; } ;
struct TYPE_12__ {struct TYPE_12__* next; int /*<<< orphan*/ * internalEventEndPtr; int /*<<< orphan*/ * internalEventPtr; int /*<<< orphan*/  betweenDecl; int /*<<< orphan*/  startTagLevel; TYPE_4__* entity; } ;
struct TYPE_10__ {scalar_t__ parsing; } ;
struct TYPE_11__ {TYPE_3__* m_freeInternalEntities; TYPE_3__* m_openInternalEntities; int /*<<< orphan*/  m_processor; TYPE_1__ m_parsingStatus; int /*<<< orphan*/  m_internalEncoding; int /*<<< orphan*/  m_tagLevel; } ;
typedef  TYPE_3__ OPEN_INTERNAL_ENTITY ;
typedef  TYPE_4__ ENTITY ;

/* Variables and functions */
 scalar_t__ MALLOC (TYPE_2__*,int) ; 
 int XML_ERROR_NONE ; 
 int XML_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  XML_FALSE ; 
 scalar_t__ XML_SUSPENDED ; 
 int /*<<< orphan*/  XML_TRUE ; 
 int XmlPrologTok (int /*<<< orphan*/ ,char const*,char const*,char const**) ; 
 int doContent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const**,int /*<<< orphan*/ ) ; 
 int doProlog (TYPE_2__*,int /*<<< orphan*/ ,char const*,char const*,int,char const*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internalEntityProcessor ; 

__attribute__((used)) static enum XML_Error
processInternalEntity(XML_Parser parser, ENTITY *entity,
                      XML_Bool betweenDecl)
{
  const char *textStart, *textEnd;
  const char *next;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY *openEntity;

  if (parser->m_freeInternalEntities) {
    openEntity = parser->m_freeInternalEntities;
    parser->m_freeInternalEntities = openEntity->next;
  }
  else {
    openEntity = (OPEN_INTERNAL_ENTITY *)MALLOC(parser, sizeof(OPEN_INTERNAL_ENTITY));
    if (!openEntity)
      return XML_ERROR_NO_MEMORY;
  }
  entity->open = XML_TRUE;
  entity->processed = 0;
  openEntity->next = parser->m_openInternalEntities;
  parser->m_openInternalEntities = openEntity;
  openEntity->entity = entity;
  openEntity->startTagLevel = parser->m_tagLevel;
  openEntity->betweenDecl = betweenDecl;
  openEntity->internalEventPtr = NULL;
  openEntity->internalEventEndPtr = NULL;
  textStart = (char *)entity->textPtr;
  textEnd = (char *)(entity->textPtr + entity->textLen);
  /* Set a safe default value in case 'next' does not get set */
  next = textStart;

#ifdef XML_DTD
  if (entity->is_param) {
    int tok = XmlPrologTok(parser->m_internalEncoding, textStart, textEnd, &next);
    result = doProlog(parser, parser->m_internalEncoding, textStart, textEnd, tok,
                      next, &next, XML_FALSE);
  }
  else
#endif /* XML_DTD */
    result = doContent(parser, parser->m_tagLevel, parser->m_internalEncoding, textStart,
                       textEnd, &next, XML_FALSE);

  if (result == XML_ERROR_NONE) {
    if (textEnd != next && parser->m_parsingStatus.parsing == XML_SUSPENDED) {
      entity->processed = (int)(next - textStart);
      parser->m_processor = internalEntityProcessor;
    }
    else {
      entity->open = XML_FALSE;
      parser->m_openInternalEntities = openEntity->next;
      /* put openEntity back in list of free instances */
      openEntity->next = parser->m_freeInternalEntities;
      parser->m_freeInternalEntities = openEntity;
    }
  }
  return result;
}