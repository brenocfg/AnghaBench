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
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ intfstream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int detect_gc_game(intfstream_t *fd, char *game_id)
{
   bool rv   = false;

   intfstream_seek(fd, 0, SEEK_SET);

   if (intfstream_read(fd, game_id, 6) > 0)
   {
      game_id[6] = '\0';
      rv = true;
   }

   return rv;
}