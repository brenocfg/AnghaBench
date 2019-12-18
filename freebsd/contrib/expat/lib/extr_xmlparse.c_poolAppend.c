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
typedef  enum XML_Convert_Result { ____Placeholder_XML_Convert_Result } XML_Convert_Result ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_4__ {int /*<<< orphan*/ * start; scalar_t__ end; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ STRING_POOL ;
typedef  int /*<<< orphan*/  ICHAR ;
typedef  int /*<<< orphan*/  ENCODING ;

/* Variables and functions */
 int const XML_CONVERT_COMPLETED ; 
 int const XML_CONVERT_INPUT_INCOMPLETE ; 
 int XmlConvert (int /*<<< orphan*/  const*,char const**,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poolGrow (TYPE_1__*) ; 

__attribute__((used)) static XML_Char *
poolAppend(STRING_POOL *pool, const ENCODING *enc,
           const char *ptr, const char *end)
{
  if (!pool->ptr && !poolGrow(pool))
    return NULL;
  for (;;) {
    const enum XML_Convert_Result convert_res = XmlConvert(enc, &ptr, end, (ICHAR **)&(pool->ptr), (ICHAR *)pool->end);
    if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
      break;
    if (!poolGrow(pool))
      return NULL;
  }
  return pool->start;
}