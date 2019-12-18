#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XML_Parser ;
typedef  scalar_t__ XML_Char ;
typedef  int /*<<< orphan*/  XML_Bool ;
struct TYPE_10__ {scalar_t__ name; } ;
struct TYPE_12__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  prefixes; TYPE_2__ defaultPrefix; int /*<<< orphan*/  generalEntities; } ;
struct TYPE_11__ {int /*<<< orphan*/  open; } ;
struct TYPE_9__ {int /*<<< orphan*/  m_tempPool; int /*<<< orphan*/  m_inheritedBindings; TYPE_4__* m_dtd; } ;
typedef  TYPE_2__ PREFIX ;
typedef  TYPE_3__ ENTITY ;
typedef  TYPE_4__ DTD ;

/* Variables and functions */
 char ASCII_EQUALS ; 
 scalar_t__ const CONTEXT_SEP ; 
 scalar_t__ XML_ERROR_NONE ; 
 int /*<<< orphan*/  XML_FALSE ; 
 scalar_t__ const XML_T (char) ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ addBinding (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ lookup (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  poolAppendChar (int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ poolCopyString (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  poolDiscard (int /*<<< orphan*/ *) ; 
 scalar_t__ poolLength (int /*<<< orphan*/ *) ; 
 scalar_t__ poolStart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static XML_Bool
setContext(XML_Parser parser, const XML_Char *context)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  const XML_Char *s = context;

  while (*context != XML_T('\0')) {
    if (*s == CONTEXT_SEP || *s == XML_T('\0')) {
      ENTITY *e;
      if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
        return XML_FALSE;
      e = (ENTITY *)lookup(parser, &dtd->generalEntities, poolStart(&parser->m_tempPool), 0);
      if (e)
        e->open = XML_TRUE;
      if (*s != XML_T('\0'))
        s++;
      context = s;
      poolDiscard(&parser->m_tempPool);
    }
    else if (*s == XML_T(ASCII_EQUALS)) {
      PREFIX *prefix;
      if (poolLength(&parser->m_tempPool) == 0)
        prefix = &dtd->defaultPrefix;
      else {
        if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
          return XML_FALSE;
        prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&parser->m_tempPool),
                                  sizeof(PREFIX));
        if (!prefix)
          return XML_FALSE;
        if (prefix->name == poolStart(&parser->m_tempPool)) {
          prefix->name = poolCopyString(&dtd->pool, prefix->name);
          if (!prefix->name)
            return XML_FALSE;
        }
        poolDiscard(&parser->m_tempPool);
      }
      for (context = s + 1;
           *context != CONTEXT_SEP && *context != XML_T('\0');
           context++)
        if (!poolAppendChar(&parser->m_tempPool, *context))
          return XML_FALSE;
      if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
        return XML_FALSE;
      if (addBinding(parser, prefix, NULL, poolStart(&parser->m_tempPool),
                     &parser->m_inheritedBindings) != XML_ERROR_NONE)
        return XML_FALSE;
      poolDiscard(&parser->m_tempPool);
      if (*context != XML_T('\0'))
        ++context;
      s = context;
    }
    else {
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return XML_FALSE;
      s++;
    }
  }
  return XML_TRUE;
}