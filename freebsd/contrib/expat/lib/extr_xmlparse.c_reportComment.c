#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_9__ {int minBytesPerChar; } ;
struct TYPE_8__ {int /*<<< orphan*/  m_tempPool; int /*<<< orphan*/  m_handlerArg; int /*<<< orphan*/  (* m_commentHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ m_defaultHandler; } ;
typedef  TYPE_2__ ENCODING ;

/* Variables and functions */
 int /*<<< orphan*/  normalizeLines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poolClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poolStoreString (int /*<<< orphan*/ *,TYPE_2__ const*,char const*,char const*) ; 
 int /*<<< orphan*/  reportDefault (TYPE_1__*,TYPE_2__ const*,char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
reportComment(XML_Parser parser, const ENCODING *enc,
              const char *start, const char *end)
{
  XML_Char *data;
  if (!parser->m_commentHandler) {
    if (parser->m_defaultHandler)
      reportDefault(parser, enc, start, end);
    return 1;
  }
  data = poolStoreString(&parser->m_tempPool,
                         enc,
                         start + enc->minBytesPerChar * 4,
                         end - enc->minBytesPerChar * 3);
  if (!data)
    return 0;
  normalizeLines(data);
  parser->m_commentHandler(parser->m_handlerArg, data);
  poolClear(&parser->m_tempPool);
  return 1;
}