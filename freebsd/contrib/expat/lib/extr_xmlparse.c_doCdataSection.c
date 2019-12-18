#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;
typedef  enum XML_Convert_Result { ____Placeholder_XML_Convert_Result } XML_Convert_Result ;
typedef  TYPE_3__* XML_Parser ;
typedef  int /*<<< orphan*/  (* XML_CharacterDataHandler ) (int /*<<< orphan*/ ,int*,int) ;
typedef  int XML_Char ;
typedef  int /*<<< orphan*/  XML_Bool ;
struct TYPE_7__ {int parsing; } ;
struct TYPE_8__ {char* m_eventPtr; char* m_eventEndPtr; int* m_dataBuf; TYPE_2__ m_parsingStatus; int /*<<< orphan*/  m_defaultHandler; int /*<<< orphan*/  m_handlerArg; scalar_t__ m_dataBufEnd; int /*<<< orphan*/  (* m_characterDataHandler ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  (* m_endCdataSectionHandler ) (int /*<<< orphan*/ ) ;TYPE_1__* m_openInternalEntities; int /*<<< orphan*/  const* m_encoding; } ;
struct TYPE_6__ {char* internalEventPtr; char* internalEventEndPtr; } ;
typedef  int /*<<< orphan*/  ICHAR ;
typedef  int /*<<< orphan*/  ENCODING ;

/* Variables and functions */
 int /*<<< orphan*/  MUST_CONVERT (int /*<<< orphan*/  const*,char const*) ; 
 int const XML_CONVERT_COMPLETED ; 
 int const XML_CONVERT_INPUT_INCOMPLETE ; 
 int XML_ERROR_ABORTED ; 
 int XML_ERROR_INVALID_TOKEN ; 
 int XML_ERROR_NONE ; 
 int XML_ERROR_PARTIAL_CHAR ; 
 int XML_ERROR_UNCLOSED_CDATA_SECTION ; 
 int XML_ERROR_UNEXPECTED_STATE ; 
#define  XML_FINISHED 136 
#define  XML_SUSPENDED 135 
#define  XML_TOK_CDATA_SECT_CLOSE 134 
#define  XML_TOK_DATA_CHARS 133 
#define  XML_TOK_DATA_NEWLINE 132 
#define  XML_TOK_INVALID 131 
#define  XML_TOK_NONE 130 
#define  XML_TOK_PARTIAL 129 
#define  XML_TOK_PARTIAL_CHAR 128 
 int XmlCdataSectionTok (int /*<<< orphan*/  const*,char const*,char const*,char const**) ; 
 int XmlConvert (int /*<<< orphan*/  const*,char const**,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reportDefault (TYPE_3__*,int /*<<< orphan*/  const*,char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static enum XML_Error
doCdataSection(XML_Parser parser,
               const ENCODING *enc,
               const char **startPtr,
               const char *end,
               const char **nextPtr,
               XML_Bool haveMore)
{
  const char *s = *startPtr;
  const char **eventPP;
  const char **eventEndPP;
  if (enc == parser->m_encoding) {
    eventPP = &parser->m_eventPtr;
    *eventPP = s;
    eventEndPP = &parser->m_eventEndPtr;
  }
  else {
    eventPP = &(parser->m_openInternalEntities->internalEventPtr);
    eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
  }
  *eventPP = s;
  *startPtr = NULL;

  for (;;) {
    const char *next;
    int tok = XmlCdataSectionTok(enc, s, end, &next);
    *eventEndPP = next;
    switch (tok) {
    case XML_TOK_CDATA_SECT_CLOSE:
      if (parser->m_endCdataSectionHandler)
        parser->m_endCdataSectionHandler(parser->m_handlerArg);
#if 0
      /* see comment under XML_TOK_CDATA_SECT_OPEN */
      else if (parser->m_characterDataHandler)
        parser->m_characterDataHandler(parser->m_handlerArg, parser->m_dataBuf, 0);
#endif
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      *startPtr = next;
      *nextPtr = next;
      if (parser->m_parsingStatus.parsing == XML_FINISHED)
        return XML_ERROR_ABORTED;
      else
        return XML_ERROR_NONE;
    case XML_TOK_DATA_NEWLINE:
      if (parser->m_characterDataHandler) {
        XML_Char c = 0xA;
        parser->m_characterDataHandler(parser->m_handlerArg, &c, 1);
      }
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_DATA_CHARS:
      {
        XML_CharacterDataHandler charDataHandler = parser->m_characterDataHandler;
        if (charDataHandler) {
          if (MUST_CONVERT(enc, s)) {
            for (;;) {
              ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
              const enum XML_Convert_Result convert_res = XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
              *eventEndPP = next;
              charDataHandler(parser->m_handlerArg, parser->m_dataBuf,
                              (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
              if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
                break;
              *eventPP = s;
            }
          }
          else
            charDataHandler(parser->m_handlerArg,
                            (XML_Char *)s,
                            (int)((XML_Char *)next - (XML_Char *)s));
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_INVALID:
      *eventPP = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_PARTIAL:
    case XML_TOK_NONE:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_CDATA_SECTION;
    default:
      /* Every token returned by XmlCdataSectionTok() has its own
       * explicit case, so this default case will never be executed.
       * We retain it as a safety net and exclude it from the coverage
       * statistics.
       *
       * LCOV_EXCL_START
      */
      *eventPP = next;
      return XML_ERROR_UNEXPECTED_STATE;
      /* LCOV_EXCL_STOP */
    }

    *eventPP = s = next;
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default: ;
    }
  }
  /* not reached */
}