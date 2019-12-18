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
 int /*<<< orphan*/  XML_ParserFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parser ; 

__attribute__((used)) static void
basic_teardown(void)
{
    if (parser != NULL) {
        XML_ParserFree(parser);
        parser = NULL;
    }
}