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
struct TYPE_3__ {int compression; int /*<<< orphan*/ * lang_key; int /*<<< orphan*/ * lang; scalar_t__ itxt_length; scalar_t__ text_length; int /*<<< orphan*/ * text; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ png_text ;
typedef  int /*<<< orphan*/  png_charp ;

/* Variables and functions */

__attribute__((used)) static void
clear_text(png_text *text, png_charp keyword)
{
   text->compression = -1; /* none */
   text->key = keyword;
   text->text = NULL;
   text->text_length = 0; /* libpng calculates this */
   text->itxt_length = 0; /* libpng calculates this */
   text->lang = NULL;
   text->lang_key = NULL;
}