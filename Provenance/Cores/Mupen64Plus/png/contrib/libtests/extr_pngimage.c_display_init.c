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
struct display {int /*<<< orphan*/  written_file; int /*<<< orphan*/ * write_pp; int /*<<< orphan*/  original_file; int /*<<< orphan*/ * read_ip; int /*<<< orphan*/ * read_pp; int /*<<< orphan*/ * original_rows; int /*<<< orphan*/ * original_ip; int /*<<< orphan*/ * original_pp; int /*<<< orphan*/ * operation; int /*<<< orphan*/ * filename; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARNINGS ; 
 int /*<<< orphan*/  buffer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct display*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
display_init(struct display *dp)
   /* Call this only once right at the start to initialize the control
    * structure, the (struct buffer) lists are maintained across calls - the
    * memory is not freed.
    */
{
   memset(dp, 0, sizeof *dp);
   dp->options = WARNINGS; /* default to !verbose, !quiet */
   dp->filename = NULL;
   dp->operation = NULL;
   dp->original_pp = NULL;
   dp->original_ip = NULL;
   dp->original_rows = NULL;
   dp->read_pp = NULL;
   dp->read_ip = NULL;
   buffer_init(&dp->original_file);

#  ifdef PNG_WRITE_PNG_SUPPORTED
      dp->write_pp = NULL;
      buffer_init(&dp->written_file);
#  endif
}