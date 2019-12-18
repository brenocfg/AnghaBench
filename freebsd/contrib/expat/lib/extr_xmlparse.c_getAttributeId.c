#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XML_Parser ;
typedef  scalar_t__ XML_Char ;
struct TYPE_11__ {scalar_t__ const* name; TYPE_2__* prefix; int /*<<< orphan*/  xmlns; } ;
struct TYPE_9__ {scalar_t__ const* name; } ;
struct TYPE_10__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  prefixes; TYPE_2__ defaultPrefix; int /*<<< orphan*/  attributeIds; } ;
struct TYPE_8__ {int /*<<< orphan*/  m_ns; TYPE_3__* m_dtd; } ;
typedef  TYPE_2__ PREFIX ;
typedef  int /*<<< orphan*/  ENCODING ;
typedef  TYPE_3__ DTD ;
typedef  TYPE_4__ ATTRIBUTE_ID ;

/* Variables and functions */
 char ASCII_COLON ; 
 char ASCII_l ; 
 char ASCII_m ; 
 char ASCII_n ; 
 char ASCII_s ; 
 char ASCII_x ; 
 scalar_t__ const XML_T (char) ; 
 int /*<<< orphan*/  XML_TRUE ; 
 scalar_t__ lookup (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  poolAppendChar (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  poolDiscard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poolFinish (int /*<<< orphan*/ *) ; 
 scalar_t__ const* poolStart (int /*<<< orphan*/ *) ; 
 scalar_t__* poolStoreString (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,char const*) ; 

__attribute__((used)) static ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc,
               const char *start, const char *end)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  ATTRIBUTE_ID *id;
  const XML_Char *name;
  if (!poolAppendChar(&dtd->pool, XML_T('\0')))
    return NULL;
  name = poolStoreString(&dtd->pool, enc, start, end);
  if (!name)
    return NULL;
  /* skip quotation mark - its storage will be re-used (like in name[-1]) */
  ++name;
  id = (ATTRIBUTE_ID *)lookup(parser, &dtd->attributeIds, name, sizeof(ATTRIBUTE_ID));
  if (!id)
    return NULL;
  if (id->name != name)
    poolDiscard(&dtd->pool);
  else {
    poolFinish(&dtd->pool);
    if (!parser->m_ns)
      ;
    else if (name[0] == XML_T(ASCII_x)
        && name[1] == XML_T(ASCII_m)
        && name[2] == XML_T(ASCII_l)
        && name[3] == XML_T(ASCII_n)
        && name[4] == XML_T(ASCII_s)
        && (name[5] == XML_T('\0') || name[5] == XML_T(ASCII_COLON))) {
      if (name[5] == XML_T('\0'))
        id->prefix = &dtd->defaultPrefix;
      else
        id->prefix = (PREFIX *)lookup(parser, &dtd->prefixes, name + 6, sizeof(PREFIX));
      id->xmlns = XML_TRUE;
    }
    else {
      int i;
      for (i = 0; name[i]; i++) {
        /* attributes without prefix are *not* in the default namespace */
        if (name[i] == XML_T(ASCII_COLON)) {
          int j;
          for (j = 0; j < i; j++) {
            if (!poolAppendChar(&dtd->pool, name[j]))
              return NULL;
          }
          if (!poolAppendChar(&dtd->pool, XML_T('\0')))
            return NULL;
          id->prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&dtd->pool),
                                        sizeof(PREFIX));
          if (!id->prefix)
            return NULL;
          if (id->prefix->name == poolStart(&dtd->pool))
            poolFinish(&dtd->pool);
          else
            poolDiscard(&dtd->pool);
          break;
        }
      }
    }
  }
  return id;
}