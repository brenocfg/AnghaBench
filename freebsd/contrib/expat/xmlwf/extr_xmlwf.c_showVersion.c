#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ feature; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ XML_Feature ;
typedef  char XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  T (char*) ; 
 int /*<<< orphan*/  XML_ExpatVersion () ; 
 scalar_t__ XML_FEATURE_END ; 
 TYPE_1__* XML_GetFeatureList () ; 
 int /*<<< orphan*/  ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
showVersion(XML_Char *prog)
{
  XML_Char *s = prog;
  XML_Char ch;
  const XML_Feature *features = XML_GetFeatureList();
  while ((ch = *s) != 0) {
    if (ch == '/'
#if defined(_WIN32)
        || ch == '\\'
#endif
        )
      prog = s + 1;
    ++s;
  }
  ftprintf(stdout, T("%s using %s\n"), prog, XML_ExpatVersion());
  if (features != NULL && features[0].feature != XML_FEATURE_END) {
    int i = 1;
    ftprintf(stdout, T("%s"), features[0].name);
    if (features[0].value)
      ftprintf(stdout, T("=%ld"), features[0].value);
    while (features[i].feature != XML_FEATURE_END) {
      ftprintf(stdout, T(", %s"), features[i].name);
      if (features[i].value)
        ftprintf(stdout, T("=%ld"), features[i].value);
      ++i;
    }
    ftprintf(stdout, T("\n"));
  }
}