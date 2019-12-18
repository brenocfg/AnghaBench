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

int detect_psp_game(intfstream_t *fd, char *game_id)
{
   unsigned pos;
   bool rv   = false;

   for (pos = 0; pos < 100000; pos++)
   {
      intfstream_seek(fd, pos, SEEK_SET);

      if (intfstream_read(fd, game_id, 5) > 0)
      {
         game_id[5] = '\0';

         if (
               (string_is_equal(game_id, "ULES-"))
               || (string_is_equal(game_id, "ULUS-"))
               || (string_is_equal(game_id, "ULJS-"))

               || (string_is_equal(game_id, "ULEM-"))
               || (string_is_equal(game_id, "ULUM-"))
               || (string_is_equal(game_id, "ULJM-"))

               || (string_is_equal(game_id, "UCES-"))
               || (string_is_equal(game_id, "UCUS-"))
               || (string_is_equal(game_id, "UCJS-"))
               || (string_is_equal(game_id, "UCAS-"))

               || (string_is_equal(game_id, "NPEH-"))
               || (string_is_equal(game_id, "NPUH-"))
               || (string_is_equal(game_id, "NPJH-"))

               || (string_is_equal(game_id, "NPEG-"))
               || (string_is_equal(game_id, "NPUG-"))
               || (string_is_equal(game_id, "NPJG-"))
               || (string_is_equal(game_id, "NPHG-"))

               || (string_is_equal(game_id, "NPEZ-"))
               || (string_is_equal(game_id, "NPUZ-"))
               || (string_is_equal(game_id, "NPJZ-"))
               )
               {
                  intfstream_seek(fd, pos, SEEK_SET);
                  if (intfstream_read(fd, game_id, 10) > 0)
                  {
#if 0
                     game_id[4] = '-';
                     game_id[8] = game_id[9];
                     game_id[9] = game_id[10];
#endif
                     game_id[10] = '\0';
                     rv = true;
                  }
                  break;
               }
      }
      else
         break;
   }

   return rv;
}