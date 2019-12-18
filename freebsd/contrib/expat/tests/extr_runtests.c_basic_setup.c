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

/* Variables and functions */
 int /*<<< orphan*/ * XML_ParserCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail (char*) ; 
 int /*<<< orphan*/ * parser ; 

__attribute__((used)) static void
basic_setup(void)
{
    parser = XML_ParserCreate(NULL);
    if (parser == NULL)
        fail("Parser not created.");
}