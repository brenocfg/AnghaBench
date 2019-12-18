#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;
typedef  int /*<<< orphan*/  encodingBuf ;
typedef  TYPE_1__* XML_Parser ;
struct TYPE_4__ {int* m_protocolEncodingName; int /*<<< orphan*/  m_encoding; int /*<<< orphan*/  m_initEncoding; scalar_t__ m_ns; } ;

/* Variables and functions */
 int XML_ERROR_NONE ; 
 scalar_t__ XmlInitEncoding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ XmlInitEncodingNS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int handleUnknownEncoding (TYPE_1__*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static enum XML_Error
initializeEncoding(XML_Parser parser)
{
  const char *s;
#ifdef XML_UNICODE
  char encodingBuf[128];
  /* See comments abount `protoclEncodingName` in parserInit() */
  if (!parser->m_protocolEncodingName)
    s = NULL;
  else {
    int i;
    for (i = 0; parser->m_protocolEncodingName[i]; i++) {
      if (i == sizeof(encodingBuf) - 1
          || (parser->m_protocolEncodingName[i] & ~0x7f) != 0) {
        encodingBuf[0] = '\0';
        break;
      }
      encodingBuf[i] = (char)parser->m_protocolEncodingName[i];
    }
    encodingBuf[i] = '\0';
    s = encodingBuf;
  }
#else
  s = parser->m_protocolEncodingName;
#endif
  if ((parser->m_ns ? XmlInitEncodingNS : XmlInitEncoding)(&parser->m_initEncoding, &parser->m_encoding, s))
    return XML_ERROR_NONE;
  return handleUnknownEncoding(parser, parser->m_protocolEncodingName);
}