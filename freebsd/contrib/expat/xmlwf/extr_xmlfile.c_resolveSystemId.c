#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ XML_Char ;

/* Variables and functions */
 scalar_t__ const T (char) ; 
 scalar_t__ isAsciiLetter (scalar_t__ const) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  tcscpy (scalar_t__*,scalar_t__ const*) ; 
 int tcslen (scalar_t__ const*) ; 
 scalar_t__* tcsrchr (scalar_t__*,scalar_t__ const) ; 

__attribute__((used)) static const XML_Char *
resolveSystemId(const XML_Char *base, const XML_Char *systemId,
                XML_Char **toFree)
{
  XML_Char *s;
  *toFree = 0;
  if (!base
      || *systemId == T('/')
#if defined(_WIN32)
      || *systemId == T('\\')
      || (isAsciiLetter(systemId[0]) && systemId[1] == T(':'))
#endif
     )
    return systemId;
  *toFree = (XML_Char *)malloc((tcslen(base) + tcslen(systemId) + 2)
                               * sizeof(XML_Char));
  if (!*toFree)
    return systemId;
  tcscpy(*toFree, base);
  s = *toFree;
  if (tcsrchr(s, T('/')))
    s = tcsrchr(s, T('/')) + 1;
#if defined(_WIN32)
  if (tcsrchr(s, T('\\')))
    s = tcsrchr(s, T('\\')) + 1;
#endif
  tcscpy(s, systemId);
  return *toFree;
}