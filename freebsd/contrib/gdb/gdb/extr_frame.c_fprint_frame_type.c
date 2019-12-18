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
struct ui_file {int dummy; } ;
typedef  enum frame_type { ____Placeholder_frame_type } frame_type ;

/* Variables and functions */
#define  DUMMY_FRAME 131 
#define  NORMAL_FRAME 130 
#define  SIGTRAMP_FRAME 129 
#define  UNKNOWN_FRAME 128 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*) ; 

__attribute__((used)) static void
fprint_frame_type (struct ui_file *file, enum frame_type type)
{
  switch (type)
    {
    case UNKNOWN_FRAME:
      fprintf_unfiltered (file, "UNKNOWN_FRAME");
      return;
    case NORMAL_FRAME:
      fprintf_unfiltered (file, "NORMAL_FRAME");
      return;
    case DUMMY_FRAME:
      fprintf_unfiltered (file, "DUMMY_FRAME");
      return;
    case SIGTRAMP_FRAME:
      fprintf_unfiltered (file, "SIGTRAMP_FRAME");
      return;
    default:
      fprintf_unfiltered (file, "<unknown type>");
      return;
    };
}