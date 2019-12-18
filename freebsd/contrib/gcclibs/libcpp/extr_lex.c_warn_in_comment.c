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
typedef  char uchar ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_3__ {char type; char* pos; } ;
typedef  TYPE_1__ _cpp_line_note ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nvspace (char const) ; 
 int /*<<< orphan*/  trigraphs ; 

__attribute__((used)) static bool
warn_in_comment (cpp_reader *pfile, _cpp_line_note *note)
{
  const uchar *p;

  /* Within comments we don't warn about trigraphs, unless the
     trigraph forms an escaped newline, as that may change
     behavior.  */
  if (note->type != '/')
    return false;

  /* If -trigraphs, then this was an escaped newline iff the next note
     is coincident.  */
  if (CPP_OPTION (pfile, trigraphs))
    return note[1].pos == note->pos;

  /* Otherwise, see if this forms an escaped newline.  */
  p = note->pos + 3;
  while (is_nvspace (*p))
    p++;

  /* There might have been escaped newlines between the trigraph and the
     newline we found.  Hence the position test.  */
  return (*p == '\n' && p < note[1].pos);
}