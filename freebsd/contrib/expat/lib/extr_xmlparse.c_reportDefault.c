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
typedef  enum XML_Convert_Result { ____Placeholder_XML_Convert_Result } XML_Convert_Result ;
typedef  TYPE_2__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_5__ {char* m_eventPtr; char* m_eventEndPtr; int /*<<< orphan*/  m_handlerArg; int /*<<< orphan*/  (* m_defaultHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * m_dataBuf; scalar_t__ m_dataBufEnd; TYPE_1__* m_openInternalEntities; int /*<<< orphan*/  const* m_encoding; } ;
struct TYPE_4__ {char* internalEventPtr; char* internalEventEndPtr; } ;
typedef  int /*<<< orphan*/  ICHAR ;
typedef  int /*<<< orphan*/  ENCODING ;

/* Variables and functions */
 scalar_t__ MUST_CONVERT (int /*<<< orphan*/  const*,char const*) ; 
 int XML_CONVERT_COMPLETED ; 
 int XML_CONVERT_INPUT_INCOMPLETE ; 
 int XmlConvert (int /*<<< orphan*/  const*,char const**,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
reportDefault(XML_Parser parser, const ENCODING *enc,
              const char *s, const char *end)
{
  if (MUST_CONVERT(enc, s)) {
    enum XML_Convert_Result convert_res;
    const char **eventPP;
    const char **eventEndPP;
    if (enc == parser->m_encoding) {
      eventPP = &parser->m_eventPtr;
      eventEndPP = &parser->m_eventEndPtr;
    }
    else {
      /* To get here, two things must be true; the parser must be
       * using a character encoding that is not the same as the
       * encoding passed in, and the encoding passed in must need
       * conversion to the internal format (UTF-8 unless XML_UNICODE
       * is defined).  The only occasions on which the encoding passed
       * in is not the same as the parser's encoding are when it is
       * the internal encoding (e.g. a previously defined parameter
       * entity, already converted to internal format).  This by
       * definition doesn't need conversion, so the whole branch never
       * gets executed.
       *
       * For safety's sake we don't delete these lines and merely
       * exclude them from coverage statistics.
       *
       * LCOV_EXCL_START
       */
      eventPP = &(parser->m_openInternalEntities->internalEventPtr);
      eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
      /* LCOV_EXCL_STOP */
    }
    do {
      ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
      convert_res = XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
      *eventEndPP = s;
      parser->m_defaultHandler(parser->m_handlerArg, parser->m_dataBuf, (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
      *eventPP = s;
    } while ((convert_res != XML_CONVERT_COMPLETED) && (convert_res != XML_CONVERT_INPUT_INCOMPLETE));
  }
  else
    parser->m_defaultHandler(parser->m_handlerArg, (XML_Char *)s, (int)((XML_Char *)end - (XML_Char *)s));
}