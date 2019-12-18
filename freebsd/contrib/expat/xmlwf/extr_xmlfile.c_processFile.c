#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_2__ {int* retPtr; int /*<<< orphan*/  parser; } ;
typedef  TYPE_1__ PROCESS_ARGS ;

/* Variables and functions */
 scalar_t__ XML_Parse (int /*<<< orphan*/ ,char const*,int,int) ; 
 scalar_t__ XML_STATUS_ERROR ; 
 int /*<<< orphan*/  reportError (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
processFile(const void *data, size_t size,
            const XML_Char *filename, void *args)
{
  XML_Parser parser = ((PROCESS_ARGS *)args)->parser;
  int *retPtr = ((PROCESS_ARGS *)args)->retPtr;
  if (XML_Parse(parser, (const char *)data, (int)size, 1) == XML_STATUS_ERROR) {
    reportError(parser, filename);
    *retPtr = 0;
  }
  else
    *retPtr = 1;
}