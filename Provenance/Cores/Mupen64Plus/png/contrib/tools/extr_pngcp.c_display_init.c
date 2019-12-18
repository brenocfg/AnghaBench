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
struct display {char* operation; char* filename; char* output_file; int min_windowBits; scalar_t__ text_stashed; scalar_t__ num_text; int /*<<< orphan*/ * text_ptr; int /*<<< orphan*/ * write_pp; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * read_pp; int /*<<< orphan*/ * fp; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARNINGS ; 
 int /*<<< orphan*/  memset (struct display*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
display_init(struct display *dp)
   /* Call this only once right at the start to initialize the control
    * structure, the (struct buffer) lists are maintained across calls - the
    * memory is not freed.
    */
{
   memset(dp, 0, sizeof *dp);
   dp->operation = "internal error";
   dp->filename = "command line";
   dp->output_file = "no output file";
   dp->options = WARNINGS; /* default to !verbose, !quiet */
   dp->fp = NULL;
   dp->read_pp = NULL;
   dp->ip = NULL;
   dp->write_pp = NULL;
   dp->min_windowBits = -1; /* this is an OPTIND, so -1 won't match anything */
#  if PNG_LIBPNG_VER < 10700 && defined PNG_TEXT_SUPPORTED
      dp->text_ptr = NULL;
      dp->num_text = 0;
      dp->text_stashed = 0;
#  endif /* pre 1.7 */
}