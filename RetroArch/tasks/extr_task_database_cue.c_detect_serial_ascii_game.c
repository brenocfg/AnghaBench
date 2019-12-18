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
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

int detect_serial_ascii_game(intfstream_t *fd, char *game_id)
{
   unsigned pos;
   int numberOfAscii = 0;
   bool rv   = false;

   for (pos = 0; pos < 10000; pos++)
   {
      intfstream_seek(fd, pos, SEEK_SET);
      if (intfstream_read(fd, game_id, 15) > 0)
      {
         unsigned i;
         game_id[15] = '\0';
         numberOfAscii = 0;

         /* When scanning WBFS files, "WBFS" is discovered as the first serial. Ignore it. */
         if (string_is_equal(game_id, "WBFS")) {
            continue;
         }

         /* Loop through until we run out of ASCII characters. */
         for (i = 0; i < 15; i++)
         {
            /* Is the given character ASCII? A-Z, 0-9, - */
            if (game_id[i] == 45 || (game_id[i] >= 48 && game_id[i] <= 57) || (game_id[i] >= 65 && game_id[i] <= 90))
               numberOfAscii++;
            else
               break;
         }

         /* If the length of the text is between 3 and 9 characters, it could be a serial. */
         if (numberOfAscii > 3 && numberOfAscii < 9)
         {
            /* Cut the string off, and return it as a valid serial. */
            game_id[numberOfAscii] = '\0';
            rv = true;
            break;
         }
      }
   }

   return rv;
}