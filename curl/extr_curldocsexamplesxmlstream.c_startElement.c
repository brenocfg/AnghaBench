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
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * memory; } ;
struct ParserStruct {TYPE_1__ characters; int /*<<< orphan*/  depth; int /*<<< orphan*/  tags; } ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void startElement(void *userData, const XML_Char *name,
                         const XML_Char **atts)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  state->tags++;
  state->depth++;

  /* Get a clean slate for reading in character data. */
  free(state->characters.memory);
  state->characters.memory = NULL;
  state->characters.size = 0;
}