#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum XML_Error { ____Placeholder_XML_Error } XML_Error ;
typedef  TYPE_1__* XML_Parser ;
struct TYPE_7__ {int* map; int /*<<< orphan*/ * data; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * convert; } ;
typedef  TYPE_2__ XML_Encoding ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_6__ {int /*<<< orphan*/ * m_encoding; int /*<<< orphan*/  (* m_unknownEncodingRelease ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * m_unknownEncodingData; int /*<<< orphan*/  m_unknownEncodingMem; scalar_t__ m_ns; int /*<<< orphan*/  m_unknownEncodingHandlerData; scalar_t__ (* m_unknownEncodingHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  ENCODING ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int XML_ERROR_NONE ; 
 int XML_ERROR_NO_MEMORY ; 
 int XML_ERROR_UNKNOWN_ENCODING ; 
 int /*<<< orphan*/ * XmlInitUnknownEncoding (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XmlInitUnknownEncodingNS (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XmlSizeOfUnknownEncoding () ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum XML_Error
handleUnknownEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (parser->m_unknownEncodingHandler) {
    XML_Encoding info;
    int i;
    for (i = 0; i < 256; i++)
      info.map[i] = -1;
    info.convert = NULL;
    info.data = NULL;
    info.release = NULL;
    if (parser->m_unknownEncodingHandler(parser->m_unknownEncodingHandlerData, encodingName,
                               &info)) {
      ENCODING *enc;
      parser->m_unknownEncodingMem = MALLOC(parser, XmlSizeOfUnknownEncoding());
      if (!parser->m_unknownEncodingMem) {
        if (info.release)
          info.release(info.data);
        return XML_ERROR_NO_MEMORY;
      }
      enc = (parser->m_ns
             ? XmlInitUnknownEncodingNS
             : XmlInitUnknownEncoding)(parser->m_unknownEncodingMem,
                                       info.map,
                                       info.convert,
                                       info.data);
      if (enc) {
        parser->m_unknownEncodingData = info.data;
        parser->m_unknownEncodingRelease = info.release;
        parser->m_encoding = enc;
        return XML_ERROR_NONE;
      }
    }
    if (info.release != NULL)
      info.release(info.data);
  }
  return XML_ERROR_UNKNOWN_ENCODING;
}