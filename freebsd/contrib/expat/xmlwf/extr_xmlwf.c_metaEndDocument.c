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
struct TYPE_2__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ XmlwfUserData ;
typedef  int /*<<< orphan*/  XML_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  T (char*) ; 
 scalar_t__ XML_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metaEndDocument(void *userData)
{
  fputts(T("</document>\n"),
         ((XmlwfUserData *)XML_GetUserData((XML_Parser) userData))->fp);
}