#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* XML_Parser ;
typedef  scalar_t__ XML_Char ;
typedef  scalar_t__ XML_Bool ;
struct TYPE_17__ {scalar_t__ const* start; } ;
struct TYPE_11__ {TYPE_1__* binding; } ;
struct TYPE_16__ {int /*<<< orphan*/  generalEntities; int /*<<< orphan*/  prefixes; TYPE_2__ defaultPrefix; } ;
struct TYPE_15__ {scalar_t__* name; int /*<<< orphan*/  open; } ;
struct TYPE_14__ {TYPE_3__* binding; scalar_t__* name; } ;
struct TYPE_13__ {TYPE_8__ m_tempPool; scalar_t__ m_namespaceSeparator; TYPE_7__* m_dtd; } ;
struct TYPE_12__ {int uriLen; scalar_t__ const* uri; } ;
struct TYPE_10__ {int uriLen; scalar_t__ const* uri; } ;
typedef  TYPE_5__ PREFIX ;
typedef  int /*<<< orphan*/  HASH_TABLE_ITER ;
typedef  TYPE_6__ ENTITY ;
typedef  TYPE_7__ DTD ;

/* Variables and functions */
 char ASCII_EQUALS ; 
 scalar_t__ const CONTEXT_SEP ; 
 scalar_t__ XML_FALSE ; 
 scalar_t__ const XML_T (char) ; 
 scalar_t__ XML_TRUE ; 
 int /*<<< orphan*/  hashTableIterInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hashTableIterNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poolAppendChar (TYPE_8__*,scalar_t__ const) ; 

__attribute__((used)) static const XML_Char *
getContext(XML_Parser parser)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  HASH_TABLE_ITER iter;
  XML_Bool needSep = XML_FALSE;

  if (dtd->defaultPrefix.binding) {
    int i;
    int len;
    if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = dtd->defaultPrefix.binding->uriLen;
    if (parser->m_namespaceSeparator)
      len--;
    for (i = 0; i < len; i++) {
      if (!poolAppendChar(&parser->m_tempPool, dtd->defaultPrefix.binding->uri[i])) {
        /* Because of memory caching, I don't believe this line can be
         * executed.
         *
         * This is part of a loop copying the default prefix binding
         * URI into the parser's temporary string pool.  Previously,
         * that URI was copied into the same string pool, with a
         * terminating NUL character, as part of setContext().  When
         * the pool was cleared, that leaves a block definitely big
         * enough to hold the URI on the free block list of the pool.
         * The URI copy in getContext() therefore cannot run out of
         * memory.
         *
         * If the pool is used between the setContext() and
         * getContext() calls, the worst it can do is leave a bigger
         * block on the front of the free list.  Given that this is
         * all somewhat inobvious and program logic can be changed, we
         * don't delete the line but we do exclude it from the test
         * coverage statistics.
         */
        return NULL; /* LCOV_EXCL_LINE */
      }
    }
    needSep = XML_TRUE;
  }

  hashTableIterInit(&iter, &(dtd->prefixes));
  for (;;) {
    int i;
    int len;
    const XML_Char *s;
    PREFIX *prefix = (PREFIX *)hashTableIterNext(&iter);
    if (!prefix)
      break;
    if (!prefix->binding) {
      /* This test appears to be (justifiable) paranoia.  There does
       * not seem to be a way of injecting a prefix without a binding
       * that doesn't get errored long before this function is called.
       * The test should remain for safety's sake, so we instead
       * exclude the following line from the coverage statistics.
       */
      continue; /* LCOV_EXCL_LINE */
    }
    if (needSep && !poolAppendChar(&parser->m_tempPool, CONTEXT_SEP))
      return NULL;
    for (s = prefix->name; *s; s++)
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return NULL;
    if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = prefix->binding->uriLen;
    if (parser->m_namespaceSeparator)
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&parser->m_tempPool, prefix->binding->uri[i]))
        return NULL;
    needSep = XML_TRUE;
  }


  hashTableIterInit(&iter, &(dtd->generalEntities));
  for (;;) {
    const XML_Char *s;
    ENTITY *e = (ENTITY *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (!e->open)
      continue;
    if (needSep && !poolAppendChar(&parser->m_tempPool, CONTEXT_SEP))
      return NULL;
    for (s = e->name; *s; s++)
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return 0;
    needSep = XML_TRUE;
  }

  if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
    return NULL;
  return parser->m_tempPool.start;
}