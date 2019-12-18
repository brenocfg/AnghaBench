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
typedef  scalar_t__ byte ;
struct TYPE_3__ {scalar_t__ errorOffset; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__* JSON_Parser ;
typedef  int /*<<< orphan*/  Error ;

/* Variables and functions */

__attribute__((used)) static void JSON_Parser_SetErrorAtStringEscapeSequenceStart(
      JSON_Parser parser, Error error, int codepointsAgo)
{
   /* Note that backtracking from the current codepoint requires us to make
      three assumptions, which are always valid in the context of a string
      escape sequence:

      1. The input encoding is not JSON_UnknownEncoding.

      2 The codepoints we are backing up across are all in the range
      U+0000 - U+007F, aka ASCII, so we can assume the number of
      bytes comprising them based on the input encoding.

      3. The codepoints we are backing up across do not include any
      line breaks, so we can assume that the line number stays the
      same and the column number can simply be decremented.
      */
   parser->error = error;
   parser->errorOffset = (byte)codepointsAgo;
}